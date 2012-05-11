#include <ptrackUi/PTrackPreferencesDialog.h>

namespace ptui {

PTrackPreferencesDialog::PTrackPreferencesDialog()
 : QDialog(),
   mUi( new Ui::PTrackPreferencesDialogBase )
{
  mUi->setupUi( this );
}

} // namespace ptui
