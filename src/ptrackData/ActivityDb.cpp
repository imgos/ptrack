#include <ptrackData/ActivityDb.h>

#include <iostream>

namespace ptdata {

/*
 * ActivityDb
 */
ActivityDb::ActivityDb( const std::string& fileName )
 : mFileName( fileName ),
   mDb( NULL )
{
  if( !sqlite3_open( fileName.c_str(), &mDb ) ) {
    std::cerr << "Failed to open database" << std::endl;
  }
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
