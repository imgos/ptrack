#ifndef ActivityDb_h
#define ActivityDb_h

#include <ptrackData/PTrackDataMacros.h>

#include <string>

struct sqlite3;

namespace ptdata {

class PTDATA_API ActivityDb
{
public:
  ActivityDb( const std::string& fileName );
  ~ActivityDb();

  bool updateDatabaseFile( const std::string& fileName );

  bool status() const;

  void categoryNameQuery( const std::string& categoryName );

private:
  std::string mFileName;

  sqlite3* mDb;
  bool mDbOkay;
};

} // namespace ptdata

#endif
