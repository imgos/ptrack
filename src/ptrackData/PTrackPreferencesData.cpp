#include <ptrackData/PTrackPreferencesData.h>

#include <QSettings>

namespace ptdata {

const QString PTrackPreferencesData::kOrgName = "imgos";
const QString PTrackPreferencesData::kAppName = "ptrack";

QByteArray PTrackPreferencesData::mWindowGeometry;
QByteArray PTrackPreferencesData::mWindowState;

PTrackPreferencesData* PTrackPreferencesData::mInstance;


/*
 * PTrackPreferencesData
 */
PTrackPreferencesData::PTrackPreferencesData()
{}

/*
 * ~PTrackPreferencesData
 */
PTrackPreferencesData::~PTrackPreferencesData()
{
  delete mInstance;
  mInstance = NULL;
}

/*
 * save
 */
void PTrackPreferencesData::save()
{
  QSettings s( kOrgName, kAppName );

  s.setValue( "ptrackui/windowgeometry", mWindowGeometry );
  s.setValue( "ptrackui/windowstate", mWindowState );
}

/*
 * create
 */
void PTrackPreferencesData::create()
{
  mInstance = new PTrackPreferencesData;

  QSettings s( kOrgName, kAppName );

  mWindowGeometry = s.value( "ptrackui/windowgeometry" ).toByteArray();
  mWindowState = s.value( "ptrackui/windowstate" ).toByteArray();
}

/*
 * instance
 */
PTrackPreferencesData* PTrackPreferencesData::instance()
{
  if( !mInstance ) {
    create();
  }

  return mInstance;
}

/*
 * windowGeometry
 */
QByteArray PTrackPreferencesData::windowGeometry()
{
  return mWindowGeometry;
}

/*
 * setWindowGeometry
 */
void PTrackPreferencesData::setWindowGeometry( QByteArray g )
{
  mWindowGeometry = g;
}

/*
 * windowState
 */
QByteArray PTrackPreferencesData::windowState()
{
  return mWindowState;
}

/*
 * setWindowState
 */
void PTrackPreferencesData::setWindowState( QByteArray s )
{
  mWindowState = s;
}

} // namespace ptdata
