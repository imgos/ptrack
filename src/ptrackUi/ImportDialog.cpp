#include <ptrackUi/ImportDialog.h>

namespace ptui {

/*
 * ImportDialog
 */
ImportDialog::ImportDialog( QWidget* parent )
 : QDialog( parent ),
   mUi( new Ui::ImportDialogBase )
{
  mUi->setupUi( this );

  // hide '?' in titlebar
  setWindowFlags( windowFlags() & ~Qt::WindowContextHelpButtonHint );
}

} // namespace ptui
