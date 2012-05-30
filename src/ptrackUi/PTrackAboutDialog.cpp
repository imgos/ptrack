#include <ptrackUi/PTrackAboutDialog.h>

namespace ptui {

/*
 * PTrackAboutDialog
 */
PTrackAboutDialog::PTrackAboutDialog( QWidget* parent )
 : QDialog( parent ),
   mUi( new Ui::PTrackAboutDialogBase )
{
  mUi->setupUi( this );

  // hide '?' in titlebar
  setWindowFlags( windowFlags() & ~Qt::WindowContextHelpButtonHint );
}

} // namespace ptui
