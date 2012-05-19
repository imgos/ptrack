#include <ptrackData/ActivityDb.h>

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
bool ActivityDb::status()
{
  return mDbOkay;
}

}
