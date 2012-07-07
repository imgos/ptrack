#include <ptrackUi/PTrackUi.h>

#include <ptrackUi/ui_PTrackUiBase.h>

#include <ptrackUi/ImportDialog.h>
#include <ptrackUi/PTrackAboutDialog.h>
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

  connect( mUi->mAboutAction, SIGNAL( triggered() ), this, SLOT( handleOpenAbout() ) );
  connect( mUi->mPreferencesAction, SIGNAL( triggered() ), this, SLOT( handleOpenPreferences() ) );
  connect( mUi->mImportAction, SIGNAL( triggered() ), this, SLOT( handleImportTriggered() ) );

  connect( mUi->mActivityListWidget, SIGNAL( currentItemChanged( QListWidgetItem*, QListWidgetItem* ) ),
    mUi->mActivityFrame, SLOT( displayActivity( QListWidgetItem*, QListWidgetItem* ) ) );

  // restore window size, position, state
  restoreGeometry( ptdata::PTrackPreferencesData::instance()->windowGeometry() );
  restoreState( ptdata::PTrackPreferencesData::instance()->windowState() );
  mUi->mSplitter->restoreState( ptdata::PTrackPreferencesData::instance()->splitterState() );
  mUi->mActivitySplitter->restoreState( ptdata::PTrackPreferencesData::instance()->activitySplitterState() );

  // load database
  mDb.reset( new ptdata::ActivityDb( ptdata::PTrackPreferencesData::instance()->dbPath().toStdString() ) );

  mUi->mActivityListWidget->populateFromActivityVector( mDb->queryAll() );
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
  ptdata::PTrackPreferencesData::instance()->setActivitySplitterState( mUi->mActivitySplitter->saveState() );
  ptdata::PTrackPreferencesData::instance()->save();
}

/*
 * handleOpenAbout
 */
void PTrackUi::handleOpenAbout()
{
  boost::scoped_ptr< PTrackAboutDialog > about(
    new PTrackAboutDialog( QString::fromStdString( mDb->version() ), this ) );
  about->exec();
}

/*
 * handleOpenPreferences
 */
void PTrackUi::handleOpenPreferences()
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

/*
 * handleImportTriggered
 */
void PTrackUi::handleImportTriggered()
{
  boost::scoped_ptr< ImportDialog > importDialog( new ImportDialog( this ) );
  importDialog->exec();
}

} //namespace ptui
