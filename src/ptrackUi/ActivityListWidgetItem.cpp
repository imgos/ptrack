#include <ptrackUi/ActivityListWidgetItem.h>

namespace ptui {

/*
 * ActivityListWidgetItem
 */
ActivityListWidgetItem::ActivityListWidgetItem(
  boost::shared_ptr< ptdata::ActivityDb::Activity > activity )
 : mActivity( activity )
{
  setText( QString( "Act: " ) + mActivity->dateTime.toString() );
}

/*
 * ActivityListWidgetItem
 */
ActivityListWidgetItem::ActivityListWidgetItem()
{}

/*
 * ~ActivityListWidgetItem
 */
ActivityListWidgetItem::~ActivityListWidgetItem()
{}

/*
 * activity
 */
boost::shared_ptr< ptdata::ActivityDb::Activity > ActivityListWidgetItem::activity()
{
  return mActivity;
}

} // namespace ptui
