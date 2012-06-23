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

} // namespace ptui
