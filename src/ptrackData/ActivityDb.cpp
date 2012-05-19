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
  if( mDb != NULL ) {
    sqlite3_close( mDb );
  }
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

} // namespace ptdata
