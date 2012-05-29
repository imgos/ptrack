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
}

} // namespace ptui
