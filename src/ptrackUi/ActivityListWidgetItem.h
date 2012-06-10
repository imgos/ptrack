#ifndef ptui_ActivityListWidgetItem_h
#define ptui_ActivityListWidgetItem_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackData/ActivityDb.h>

#include <QListWidgetItem>

namespace ptui {

class PTUI_API ActivityListWidgetItem : public QListWidgetItem
{
public:
  ActivityListWidgetItem( ptdata::ActivityDb::Activity activity );
  ActivityListWidgetItem();
  virtual ~ActivityListWidgetItem();

private:
  ptdata::ActivityDb::Activity mActivity;
};

} // namespace ptui

#endif
