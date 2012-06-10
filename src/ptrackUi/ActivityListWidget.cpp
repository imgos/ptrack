#include <ptrackUi/ActivityListWidget.h>

#include <ptrackUi/ActivityListWidgetItem.h>

namespace ptui {

/*
 * ActivityListWidget
 */
ActivityListWidget::ActivityListWidget( QWidget* parent )
 : QListWidget( parent )
{}

/*
 * ~ActivityListWidget
 */
ActivityListWidget::~ActivityListWidget()
{}

/*
 * populateFromActivityVector
 */
void ActivityListWidget::populateFromActivityVector( std::vector< ptdata::ActivityDb::Activity > activities )
{
  std::vector< ptdata::ActivityDb::Activity >::const_iterator it = activities.begin();

  while( it != activities.end() ) {
    addItem( new ActivityListWidgetItem( *it ) );
    it++;
  }
}

} // namespace ptui
