#include <ptrackUi/PTrackPreferencesDialog.h>

#include <ptrackData/PTrackPreferencesData.h>

#include <QFileDialog>

namespace ptui {

/*
 * PTrackPreferencesDialog
 */
PTrackPreferencesDialog::PTrackPreferencesDialog( QWidget* parent )
 : QDialog( parent ),
   mUi( new Ui::PTrackPreferencesDialogBase )
{
  mUi->setupUi( this );

  connect( mUi->mDbPathButton, SIGNAL( clicked() ), this, SLOT( dbPathButtonClicked() ) );

  mUi->mDbPathLineEdit->setText( ptdata::PTrackPreferencesData::instance()->dbPath() );
}

/*
 * accept
 */
void PTrackPreferencesDialog::accept()
{
  ptdata::PTrackPreferencesData::instance()->setDbPath( mUi->mDbPathLineEdit->text() );
  close();

  emit prefsChanged();
}

/*
 * dbPathButtonClicked
 */
void PTrackPreferencesDialog::dbPathButtonClicked()
{
  QFileInfo info( ptdata::PTrackPreferencesData::instance()->dbPath() );

  QString file = QFileDialog::getSaveFileName(
    this,
    "Select Database File",
    info.path(),
    "SQlite3 Database (*.sqlite3 *.db);;All Files (*.*)",
    0,
    QFileDialog::DontConfirmOverwrite );

  if( !file.isEmpty() ) {
    mUi->mDbPathLineEdit->setText( file );
  }
}

} // namespace ptui
