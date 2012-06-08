#ifndef ptdata_ActivityDb_h
#define ptdata_ActivityDb_h

#include <ptrackData/PTrackDataMacros.h>

#include <QDateTime>

#include <string>
#include <vector>

struct sqlite3;
struct sqlite3_stmt;

namespace ptdata {

class PTDATA_API ActivityDb
{
public:

  struct Activity {
    Activity( const std::string& iCategory,
      const QDateTime& iDateTime,
      const std::string& iGpsTrack,
      const double& iTotalTime,
      const double& iTotalDistance,
      const int& iUniqueId = -1 )
     : category( iCategory ),
       dateTime( iDateTime ),
       gpsTrack( iGpsTrack ),
       totalTime( iTotalTime ),
       totalDistance( iTotalDistance ),
       uniqueId( iUniqueId )
    {}

    Activity()
     : uniqueId( -1 )
    {}

    int uniqueId;
    std::string category;
    QDateTime dateTime;
    std::string gpsTrack;
    double totalTime;
    double totalDistance;
  };


  ActivityDb( const std::string& fileName );
  ~ActivityDb();

  bool updateDatabaseFile( const std::string& fileName );

  bool status() const;

  void categoryNameQuery( const std::string& categoryName );

  bool updateActivity( const std::string& category,
    const QDateTime& dateTime,
    const std::string& gpsTrack,
    const double& totalTime,
    const double& totalDistance,
    const int& uniqueId );
  bool updateActivity( const Activity& activity );

  bool insertActivity( const std::string& category,
    const QDateTime& dateTime,
    const std::string& gpsTrack,
    const double& totalTime,
    const double& totalDistance,
    const int& uniqueId,
    long& newRowId );
  bool insertActivity( const Activity& activity, long& newRowId );

  Activity rowToActivity( sqlite3_stmt* statement );
  std::vector< Activity > queryAll();

private:
  std::string mFileName;

  sqlite3* mDb;
  bool mDbOkay;
};

} // namespace ptdata

#endif
