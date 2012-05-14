#include <ptrackUi/PTrackUi.h>

#include <ptrackUi/ui_PTrackUiBase.h>

#include <ptrackUi/PTrackPreferencesDialog.h>

#include <ptrackData/PTrackPreferencesData.h>

#include <QCloseEvent>

namespace ptui {

/*
 * PTrackUi
 */
PTrackUi::PTrackUi( QWidget* parent )
 : QMainWindow( parent ),
   mUi( new Ui::PTrackUiBase )
{
  mUi->setupUi( this );

  connect( mUi->mPreferencesAction, SIGNAL( triggered() ), this, SLOT( openPreferences() ) );

  // restore window size, position, state
  restoreGeometry( ptdata::PTrackPreferencesData::instance()->windowGeometry() );
  restoreState( ptdata::PTrackPreferencesData::instance()->windowState() );
  mUi->mSplitter->restoreState( ptdata::PTrackPreferencesData::instance()->splitterState() );

  // load database
  mDb.reset( new ptdata::ActivityDb( ptdata::PTrackPreferencesData::instance()->dbPath().toStdString() ) );
}

/*
 * closeEvent
 */
void PTrackUi::closeEvent( QCloseEvent* e )
{
  // save settings
  ptdata::PTrackPreferencesData::instance()->setWindowGeometry( saveGeometry() );
  ptdata::PTrackPreferencesData::instance()->setWindowState( saveState() );
  ptdata::PTrackPreferencesData::instance()->setSplitterState( mUi->mSplitter->saveState() );
  ptdata::PTrackPreferencesData::instance()->save();
}

/*
 * openPreferences
 */
void PTrackUi::openPreferences()
{
  boost::scoped_ptr< PTrackPreferencesDialog > prefs( new PTrackPreferencesDialog( this ) );
  connect( prefs.get(), SIGNAL( prefsChanged() ), this, SLOT( handlePrefsChanged() ) );

  prefs->exec();
}

/*
 * handlePrefsChanged
 */
void PTrackUi::handlePrefsChanged()
{
  // database file may have changed
  mDb->updateDatabaseFile( ptdata::PTrackPreferencesData::instance()->dbPath().toStdString() );
}

} //namespace ptui
