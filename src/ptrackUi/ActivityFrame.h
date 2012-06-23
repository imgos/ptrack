#ifndef ptui_ActivityFrame_h
#define ptui_ActivityFrame_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackUi/ui_ActivityFrameBase.h>

#include <boost/scoped_ptr.hpp>

namespace ptui {

class PTUI_API ActivityFrame : public QFrame
{
  Q_OBJECT

public:
  ActivityFrame( QWidget* parent = 0 );

private:
  boost::scoped_ptr< ::Ui::ActivityFrameBase > mUi;
};

} // namespace ptui

#endif
