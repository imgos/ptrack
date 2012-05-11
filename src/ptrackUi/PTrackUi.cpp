#include <ptrackUi/PTrackUi.h>

#include <ptrackUi/ui_PTrackUiBase.h>

PTrackUi::PTrackUi()
 : QMainWindow(),
   mUi( new Ui::PTrackUiBase )
{
  mUi->setupUi( this );
}
