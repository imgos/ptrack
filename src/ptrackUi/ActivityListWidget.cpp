#include <ptrackUi/ActivityListWidget.h>

#include <ptrackUi/ActivityListWidgetItem.h>

#include <QAction>
#include <QMenu>

#include <boost/scoped_ptr.hpp>

namespace ptui {

/*
 * ActivityListWidget
 */
ActivityListWidget::ActivityListWidget( QWidget* parent )
 : QListWidget( parent )
{
  setContextMenuPolicy( Qt::CustomContextMenu );

  connect( this, SIGNAL( customContextMenuRequested( const QPoint& ) ),
    SLOT( handleCustomContextMenu( const QPoint& ) ) );
}

/*
 * ~ActivityListWidget
 */
ActivityListWidget::~ActivityListWidget()
{}

/*
 * populateFromActivityVector
 */
void ActivityListWidget::populateFromActivityVector(
  std::vector< boost::shared_ptr< ptdata::ActivityDb::Activity > > activities )
{
  std::vector< boost::shared_ptr< ptdata::ActivityDb::Activity > >::const_iterator it =
    activities.begin();

  while( it != activities.end() ) {
    addItem( new ActivityListWidgetItem( *it ) );
    it++;
  }

  // if we load at least 1 item, select the first
  if( activities.size() > 0 ) {
    setCurrentRow( 0 );
  }
}

/*
 * handleCustomContextMenu
 */
void ActivityListWidget::handleCustomContextMenu( const QPoint& pos )
{
  QListWidgetItem* item = itemAt( pos );

  if( !item ) {
    return;
  }

  ActivityListWidgetItem* activityItem = dynamic_cast< ActivityListWidgetItem* >( item );

  if( !activityItem ) {
    return;
  }

  // found a valid ActivityListWidgetItem at position of event, show menu
  QMenu contextMenu;

  boost::scoped_ptr< QAction > removeAction(
    new QAction( QIcon( ":/remove.png" ), "Remove", &contextMenu ) );
  connect( removeAction.get(), SIGNAL( triggered() ), this, SLOT( handleRemoveSelectedItem() ) );
  contextMenu.addAction( removeAction.get() );

  contextMenu.exec( mapToGlobal( pos ) );
}

/*
 * handleRemoveSelectedItem
 */
void ActivityListWidget::handleRemoveSelectedItem()
{
  // context menu triggers this, remove the currently selected item in the listwidget
  QListWidgetItem* itemToRemove = takeItem( currentRow() );

  if( !itemToRemove ) {
    return;
  }

  ActivityListWidgetItem* activityItemToRemove = dynamic_cast< ActivityListWidgetItem* >( itemToRemove );

  if( !activityItemToRemove ) {
    return;
  }

  delete activityItemToRemove;
}

} // namespace ptui
