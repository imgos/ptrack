#include <ptrackUi/ActivityFrame.h>

namespace ptui {

/*
 * ActivityFrame
 */
ActivityFrame::ActivityFrame( QWidget* parent )
 : QFrame( parent ),
   mUi( new Ui::ActivityFrameBase )
{
  mUi->setupUi( this );
}

} // namespace ptui
