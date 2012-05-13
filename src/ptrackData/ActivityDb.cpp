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
  if( !sqlite3_open( fileName.c_str(), &mDb ) ) {
    std::cerr << "Failed to open database" << std::endl;
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
