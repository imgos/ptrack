#ifndef ActivityDb_h
#define ActivityDb_h

#include <ptrackData/PTrackDataMacros.h>

#include <QDateTime>

#include <string>

struct sqlite3;

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

private:
  std::string mFileName;

  sqlite3* mDb;
  bool mDbOkay;
};

} // namespace ptdata

#endif
