#include <ptrackData/ActivityDb.h>

#include <boost/algorithm/string.hpp>

#include <sqlite3.h>

#include <iostream>

namespace ptdata {

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
    "    totalDistance REAL )";

  retVal = sqlite3_exec( mDb, createDbQuery, 0, 0, 0 );

  if( retVal != SQLITE_OK ) {
    std::cerr << "Failed to configure database." << std::endl;
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

} // namespace ptdata
