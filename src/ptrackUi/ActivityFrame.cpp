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
  mUi->mCategoryLineEdit->setText( QString::fromStdString( activity->category ) );
  mUi->mStartDateTimeEdit->setDateTime( activity->dateTime );

  mUi->mTotalDistanceSpinBox->setValue( activity->totalDistance );

  QTime t( 0, 0, 0, 0 );
  t = t.addSecs( (int) activity->totalTime );
  t = t.addMSecs( (int) ( ( activity->totalTime - (int) activity->totalTime ) * 1000 ) );
  mUi->mTotalTimeEdit->setTime( t );
}

/*
 * displayActivity
 */
void ActivityFrame::displayActivity( QListWidgetItem* item, QListWidgetItem* oldItem )
{
  ActivityListWidgetItem* activityItem = dynamic_cast< ActivityListWidgetItem* >( item );

  if( activityItem ) {
    displayActivity( activityItem->activity() );
  } else {
    // no selection, empty the display
    mUi->mCategoryLineEdit->setText( "" );
    mUi->mStartDateTimeEdit->setDateTime( QDateTime( QDate( 1900, 1, 1 ), QTime( 0, 0, 0, 0 ) ) );

    mUi->mTotalDistanceSpinBox->setValue( 0. );
    mUi->mTotalTimeEdit->setTime( QTime( 0, 0, 0, 0 ) );
  }
}

} // namespace ptui
