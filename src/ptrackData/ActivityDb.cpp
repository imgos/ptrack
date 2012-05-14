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
  int retVal = sqlite3_open( fileName.c_str(), &mDb );
  if( retVal != SQLITE_OK ) {
    std::cerr << "Failed to open database" << std::endl;
    sqlite3_close( mDb );
    return;
  }

  mDbOkay = true;
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

}
