#include <ptrackData/ActivityDb.h>

#include <boost/algorithm/string.hpp>

#include <sqlite3.h>

#include <iostream>
#include <sstream>

namespace ptdata {

const int ActivityDb::kMajorVersionNumber = 0;
const int ActivityDb::kMinorVersionNumber = 0;
const int ActivityDb::kPatchVersionNumber = 0;
const char* ActivityDb::kVersionDescription = "initial";

/*
 * ActivityDb
 */
ActivityDb::ActivityDb( const std::string& fileName )
 : mFileName( fileName ),
   mDb( NULL ),
   mDbOkay( false )
{
  mDbOkay = updateDatabaseFile( fileName );
}

/*
 * ~ActivityDb
 */
ActivityDb::~ActivityDb()
{
  // calling close on a null db is okay
  sqlite3_close( mDb );
}

/*
 * version
 */
void ActivityDb::version( int& major, int& minor, int& patch, std::string& description )
{
  const char* q = "SELECT major, minor, patch, description FROM versioninfo " \
                  "  ORDER BY major DESC, minor DESC, patch DESC LIMIT 1";

  sqlite3_stmt* statement;

  if( sqlite3_prepare_v2( mDb, q, -1, &statement, NULL ) != SQLITE_OK ) {
    return;
  }

  if( sqlite3_step( statement ) != SQLITE_ROW ) {
    return;
  }

  major = sqlite3_column_int( statement, 0 );
  minor = sqlite3_column_int( statement, 1 );
  patch = sqlite3_column_int( statement, 2 );
  description = std::string( (const char*)sqlite3_column_text( statement, 3 ) );

  sqlite3_finalize( statement );
}

/*
 * version
 */
std::string ActivityDb::version()
{
  int major, minor, patch;
  std::string description;

  version( major, minor, patch, description );

  std::stringstream versionStream;
  versionStream << major << "." << minor << "." << patch << " (" << description << ")";

  return versionStream.str();
}

/*
 * updateDatabaseFile
 */
bool ActivityDb::updateDatabaseFile( const std::string& fileName )
{
  sqlite3_close( mDb );

  int retVal = sqlite3_open( fileName.c_str(), &mDb );
  if( retVal != SQLITE_OK ) {
    std::cerr << "Failed to open database" << std::endl;
    sqlite3_close( mDb );
    return false;
  }

  const char* createDbQuery =
    "CREATE TABLE IF NOT EXISTS " \
    "  activity ( category TEXT, " \
    "    dateTime TEXT, " \
    "    gpsRoute BLOB, " \
    "    totalTime REAL, " \
    "    totalDistance REAL );" \
    "CREATE TABLE IF NOT EXISTS " \
    "  versioninfo ( major INTEGER, " \
    "    minor INTEGER, " \
    "    patch INTEGER, " \
    "    description TEXT, " \
    "    UNIQUE ( major, minor, patch ) ON CONFLICT REPLACE )";

  retVal = sqlite3_exec( mDb, createDbQuery, 0, 0, 0 );

  if( retVal != SQLITE_OK ) {
    std::cerr << "Failed to configure database." << std::endl;
    return false;
  }

  const char* vInsert = "INSERT INTO versioninfo ( major, minor, patch, description ) " \
                        "  VALUES ( ?, ?, ?, ? )";

  sqlite3_stmt* statement;

  if( sqlite3_prepare_v2( mDb, vInsert, -1, &statement, NULL ) != SQLITE_OK ) {
    return false;
  }

  sqlite3_bind_int( statement, 1, kMajorVersionNumber );
  sqlite3_bind_int( statement, 2, kMinorVersionNumber );
  sqlite3_bind_int( statement, 3, kPatchVersionNumber );
  sqlite3_bind_text( statement, 4, kVersionDescription, -1, SQLITE_STATIC );

  if( sqlite3_step( statement ) != SQLITE_DONE ) {
    return false;
  }

  if( sqlite3_finalize( statement ) != SQLITE_OK ) {
    return false;
  }

  return true;
}

/*
 * status
 */
bool ActivityDb::status() const
{
  return mDbOkay;
}

/*
 * categoryNameQuery
 */
void ActivityDb::categoryNameQuery( const std::string& categoryName )
{
  if( !status() ) {
    return;
  }

  std::string cleanUp = categoryName;
  boost::replace_all( cleanUp, "%", "" );

  std::string q = "SELECT * FROM activity WHERE category LIKE \"%" + cleanUp + "%\"";

  sqlite3_stmt* statement;

  int retVal = sqlite3_prepare_v2( mDb, q.c_str(), q.length(), &statement, NULL );
  if( retVal != SQLITE_OK ) {
    return;
  }

  // step through results
  int columns = sqlite3_column_count( statement );

  while( 1 ) {
    retVal = sqlite3_step( statement );

    if( retVal == SQLITE_ROW ) {
      for( int col = 0; col < columns; col++ ) {
        const char* columnName = sqlite3_column_name( statement, col );
        std::cerr << columnName << ": ";

        switch( sqlite3_column_type( statement, col ) ) {
          case SQLITE_TEXT: {
            const unsigned char* textColVal = sqlite3_column_text( statement, col );
            std::cerr << textColVal << std::endl;
            break;;
          }

          case SQLITE_FLOAT: {
            double doubleColVal = sqlite3_column_double( statement, col );
            std::cerr << doubleColVal << std::endl;
            break;;
          }
        }
      }
    } else if( retVal == SQLITE_DONE ) {
      break;
    } else {
      // an error occurred
      break;
    }
  }
}

/*
 * updateActivity
 */
bool ActivityDb::updateActivity( const std::string& category,
  const QDateTime& dateTime,
  const std::string& gpsTrack,
  const double& totalTime,
  const double& totalDistance,
  const int& uniqueId )
{
  return updateActivity( Activity( category, dateTime, gpsTrack, totalTime, totalDistance, uniqueId ) );
}

/*
 * updateActivity
 */
bool ActivityDb::updateActivity( const Activity& activity )
{
  if( !status() ) {
    return false;
  }

  sqlite3_stmt* statement;

  const char* sql = "UPDATE activity SET " \
                    "  category = ?, " \
                    "  dateTime = ?, " \
                    "  gpsTrack = ?, " \
                    "  totalTime = ?, " \
                    "  totalDistance = ? " \
                    "WHERE rowid = ?";

  int retVal = sqlite3_prepare_v2( mDb, sql, -1, &statement, NULL );
  if( retVal != SQLITE_OK ) {
    std::cerr << "sqlite prepare failed" << std::endl;
    return false;
  }

  // safely bind data
  sqlite3_bind_text( statement, 1, activity.category.c_str(), -1, SQLITE_TRANSIENT );
  QString dateString = activity.dateTime.toString();
  std::string dateStdString = dateString.toStdString();
  sqlite3_bind_text( statement, 2, dateStdString.c_str(), -1, SQLITE_TRANSIENT );
  sqlite3_bind_text( statement, 3, activity.gpsTrack.c_str(), -1, SQLITE_TRANSIENT );
  sqlite3_bind_double( statement, 4, activity.totalTime );
  sqlite3_bind_double( statement, 5, activity.totalDistance );
  sqlite3_bind_int( statement, 6, activity.uniqueId );

  // execute the update
  if( sqlite3_step( statement ) != SQLITE_OK ) {
    std::cerr << "database update failed" << std::cerr;
    return false;
  }

  if( sqlite3_finalize( statement ) != SQLITE_OK ) {
    std::cerr << "sqlite finalize failed" << std::cerr;
    return false;
  }

  return true;
}

/*
 * insertActivity
 */
bool ActivityDb::insertActivity( const std::string& category,
    const QDateTime& dateTime,
    const std::string& gpsTrack,
    const double& totalTime,
    const double& totalDistance,
    const int& uniqueId,
    long& newRowId )
{
  return insertActivity( Activity( category, dateTime, gpsTrack, totalTime, totalDistance, uniqueId ), newRowId );
}

/*
 * insertActivity
 */
bool ActivityDb::insertActivity( const Activity& activity, long& newRowId )
{
  if( !status() ) {
    return false;
  }

  sqlite3_stmt* statement;

  const char* sql = "INSERT INTO activity ( category, dateTime, gpsTrack, totalTime, totalDistance ) " \
                    "VALUES( ?, ?, ?, ?, ? )";

  int retVal = sqlite3_prepare_v2( mDb, sql, -1, &statement, NULL );
  if( retVal != SQLITE_OK ) {
    std::cerr << "sqlite prepare failed" << std::endl;
    return false;
  }

  // safely bind data
  sqlite3_bind_text( statement, 1, activity.category.c_str(), -1, SQLITE_TRANSIENT );
  QString dateString = activity.dateTime.toString();
  std::string dateStdString = dateString.toStdString();
  sqlite3_bind_text( statement, 2, dateStdString.c_str(), -1, SQLITE_TRANSIENT );
  sqlite3_bind_text( statement, 3, activity.gpsTrack.c_str(), -1, SQLITE_TRANSIENT );
  sqlite3_bind_double( statement, 4, activity.totalTime );
  sqlite3_bind_double( statement, 5, activity.totalDistance );

  // execute the update
  if( sqlite3_step( statement ) != SQLITE_OK ) {
    std::cerr << "database update failed" << std::cerr;
    return false;
  }

  newRowId = sqlite3_last_insert_rowid( mDb );

  if( sqlite3_finalize( statement ) != SQLITE_OK ) {
    std::cerr << "sqlite finalize failed" << std::cerr;
    return false;
  }

  return true;
}

/*
 * rowToActivity
 */
boost::shared_ptr< ActivityDb::Activity > ActivityDb::rowToActivity( sqlite3_stmt* statement )
{
  boost::shared_ptr< Activity > activity( new Activity );

  activity->uniqueId = sqlite3_column_int( statement, 0 );
  activity->category = std::string( (const char*) sqlite3_column_text( statement, 1 ) );
  activity->dateTime = QDateTime::fromString(
    (const char*) sqlite3_column_text( statement, 2 ),
    Qt::ISODate );

  //activity->gpsRoute = sqlite3_column_blob( statement, 3 );
  //activity->gpsRoute

  activity->totalTime = sqlite3_column_int( statement, 4 );
  activity->totalDistance = sqlite3_column_int( statement, 5 );

  return activity;
}

/*
 * queryAll
 */
std::vector< boost::shared_ptr< ptdata::ActivityDb::Activity > > ActivityDb::queryAll()
{
  const char* sql = "SELECT rowid, * FROM activity ORDER BY dateTime ASC";

  sqlite3_stmt* statement;

  int retVal = sqlite3_prepare_v2( mDb, sql, -1, &statement, NULL );

  std::vector< boost::shared_ptr< Activity > > activityVector;

  while( 1 ) {
    int stepType = sqlite3_step( statement );

    if( stepType == SQLITE_ROW ) {
      // read this row into an Activity
      activityVector.push_back( rowToActivity( statement ) );
    } else if( stepType == SQLITE_DONE ) {
      break;
    } else {
      std::cerr << "Error occurred stepping through DB rows." << std::endl;
      break;
    }
  }

  if( sqlite3_finalize( statement ) != SQLITE_OK ) {
    std::cerr << "sqlite finalize failed" << std::cerr;
  }

  return activityVector;
}

} // namespace ptdata
