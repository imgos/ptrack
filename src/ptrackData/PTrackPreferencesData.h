#ifndef PTrackPreferencesData_h
#define PTrackPreferencesData_h

#include <ptrackData/PTrackDataMacros.h>

#include <QByteArray>
#include <QString>


namespace ptdata {

class PTDATA_API PTrackPreferencesData
{
public:
  static PTrackPreferencesData* instance();

  void save();

  QByteArray windowGeometry();
  void setWindowGeometry( QByteArray g );

  QByteArray windowState();
  void setWindowState( QByteArray s );

protected:
  static void create();

private:
  PTrackPreferencesData();
  ~PTrackPreferencesData();

  static const QString kOrgName;
  static const QString kAppName;

  static QByteArray mWindowGeometry;
  static QByteArray mWindowState;

  static PTrackPreferencesData* mInstance;
};

} // namespace ptdata

#endif
