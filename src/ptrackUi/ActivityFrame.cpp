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

/*
 * displayActivity
 */
void ActivityFrame::displayActivity( boost::shared_ptr< ptdata::ActivityDb::Activity > activity )
{

}

} // namespace ptui
