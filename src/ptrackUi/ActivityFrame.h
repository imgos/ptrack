#ifndef ptui_ActivityFrame_h
#define ptui_ActivityFrame_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackUi/ui_ActivityFrameBase.h>

#include <ptrackUi/ActivityListWidgetItem.h>

#include <ptrackData/ActivityDb.h>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace ptui {

class PTUI_API ActivityFrame : public QFrame
{
  Q_OBJECT

public:
  ActivityFrame( QWidget* parent = 0 );

public Q_SLOTS:
  void displayActivity( boost::shared_ptr< ptdata::ActivityDb::Activity > activity );
  void displayActivity( QListWidgetItem* item, QListWidgetItem* oldItem );

private:
  boost::scoped_ptr< ::Ui::ActivityFrameBase > mUi;
};

} // namespace ptui

#endif
