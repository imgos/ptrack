#include <ptrackData/PTrackPreferencesData.h>

#include <QSettings>

namespace ptdata {

const QString PTrackPreferencesData::kOrgName = "imgos";
const QString PTrackPreferencesData::kAppName = "ptrack";

QByteArray PTrackPreferencesData::mWindowGeometry;
QByteArray PTrackPreferencesData::mWindowState;
QByteArray PTrackPreferencesData::mSplitterState;
QByteArray PTrackPreferencesData::mActivitySplitterState;

QString PTrackPreferencesData::mDbPath;

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
  s.setValue( "ptrackui/splitterstate", mSplitterState );
  s.setValue( "ptrackui/activitysplitterstate", mActivitySplitterState );

  s.setValue( "ptrackdata/dbpath", mDbPath );
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
  mSplitterState = s.value( "ptrackui/splitterstate" ).toByteArray();
  mActivitySplitterState = s.value( "ptrackui/activitysplitterstate" ).toByteArray();

  mDbPath = s.value( "ptrackdata/dbpath" ).toString();
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

/*
 * splitterState
 */
QByteArray PTrackPreferencesData::splitterState()
{
  return mSplitterState;
}

/*
 * setSplitterState
 */
void PTrackPreferencesData::setSplitterState( QByteArray s )
{
  mSplitterState = s;
}

/*
 * activitySplitterState
 */
QByteArray PTrackPreferencesData::activitySplitterState()
{
  return mActivitySplitterState;
}

/*
 * setActivitySplitterState
 */
void PTrackPreferencesData::setActivitySplitterState( QByteArray s )
{
  mActivitySplitterState = s;
}

/*
 * dbPath
 */
QString PTrackPreferencesData::dbPath()
{
  return mDbPath;
}

/*
 * setDbPath
 */
void PTrackPreferencesData::setDbPath( QString path )
{
  mDbPath = path;
}

} // namespace ptdata
