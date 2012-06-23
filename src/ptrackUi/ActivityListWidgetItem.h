#ifndef ptui_ActivityListWidgetItem_h
#define ptui_ActivityListWidgetItem_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackData/ActivityDb.h>

#include <QListWidgetItem>

#include <boost/shared_ptr.hpp>

namespace ptui {

class PTUI_API ActivityListWidgetItem : public QListWidgetItem
{
public:
  ActivityListWidgetItem( boost::shared_ptr< ptdata::ActivityDb::Activity > activity );
  ActivityListWidgetItem();
  virtual ~ActivityListWidgetItem();

private:
  boost::shared_ptr< ptdata::ActivityDb::Activity > mActivity;
};

} // namespace ptui

#endif
