#include <ptrackUi/PTrackAboutDialog.h>

namespace ptui {

/*
 * PTrackAboutDialog
 */
PTrackAboutDialog::PTrackAboutDialog( QWidget* parent )
 : QDialog( parent ),
   mUi( new Ui::PTrackAboutDialogBase )
{
  init();
}

/*
 * PTrackAboutDialog
 */
PTrackAboutDialog::PTrackAboutDialog( const QString& databaseVersion, QWidget* parent )
 : QDialog( parent ),
   mUi( new Ui::PTrackAboutDialogBase )
{
  init( databaseVersion );
}

/*
 * init
 */
void PTrackAboutDialog::init( const QString& databaseVersion )
{
  mUi->setupUi( this );

  // hide '?' in titlebar
  setWindowFlags( windowFlags() & ~Qt::WindowContextHelpButtonHint );

  if( databaseVersion.compare( "" ) != 0 ) {
    mUi->mTextEdit->append( "Database version: " + databaseVersion );
  }
}

} // namespace ptui
