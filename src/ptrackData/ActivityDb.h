#ifndef ActivityDb_h
#define ActivityDb_h

#include <ptrackData/PTrackDataMacros.h>

#include <sqlite3.h>

#include <string>

namespace ptdata {

class PTDATA_API ActivityDb
{
public:
  ActivityDb( const std::string& fileName );
  ~ActivityDb();

private:
  std::string mFileName;
  sqlite3* mDb;
};

}

#endif
