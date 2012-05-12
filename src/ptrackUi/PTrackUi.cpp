#include <ptrackUi/PTrackUi.h>

#include <ptrackUi/ui_PTrackUiBase.h>

#include <ptrackUi/PTrackPreferencesDialog.h>

#include <ptrackData/PTrackPreferencesData.h>

#include <QCloseEvent>

namespace ptui {

/*
 * PTrackUi
 */
PTrackUi::PTrackUi()
 : QMainWindow(),
   mUi( new Ui::PTrackUiBase )
{
  mUi->setupUi( this );

  connect( mUi->mPreferencesAction, SIGNAL( triggered() ), this, SLOT( openPreferences() ) );

  // restore window size, position, state
  restoreGeometry( ptdata::PTrackPreferencesData::instance()->windowGeometry() );
  restoreState( ptdata::PTrackPreferencesData::instance()->windowState() );
  mUi->mSplitter->restoreState( ptdata::PTrackPreferencesData::instance()->splitterState() );
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
  boost::scoped_ptr< PTrackPreferencesDialog > prefs( new PTrackPreferencesDialog );
  prefs->exec();
}

} //namespace ptui
