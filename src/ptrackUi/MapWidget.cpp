#include <ptrackUi/MapWidget.h>

#include <QDebug>

namespace ptui {

const char* MapWidget::kHtml = "<html><head><script type=\"text/javascript\" " \
    "src=\"http://maps.google.com/maps/api/js?sensor=false\"></script>" \
    "<script  type=\"text/javascript\">" \
    "var map; function init(lat, lng) { "\
    "map = new google.maps.Map(document.getElementById(\"map_canvas\"), " \
    "{ zoom: 5, center: new google.maps.LatLng(lat, lng), " \
    "disableDefaultUI: true, mapTypeId: google.maps.MapTypeId.ROADMAP  });" \
    "} </script>" \
    "</head><body style=\"margin:0px; padding:0px;\">" \
    "<div id=\"map_canvas\" style=\"width:100%; height:100%\"></div>" \
    "</body></html>";

/*
 * MapWidget
 */
MapWidget::MapWidget( QWidget* parent )
 : QWebView( parent ),
   mNetManager( new QNetworkAccessManager( this ) ),
   mPressed( false )
{
  QWebFrame* frame = page()->mainFrame();
  frame->setHtml( QString( kHtml ) );

  QTimer::singleShot( 1000, this, SLOT( triggerLoading() ) );
}

/*
 * triggerLoading
 */
void MapWidget::triggerLoading()
{
  QString code = "init(37.6970, -91.8096)";
  QWebFrame *frame = page()->mainFrame();
  frame->evaluateJavaScript( code );
}

/*
 * timerEvent
 */
void MapWidget::timerEvent( QTimerEvent* event )
{
  qDebug() << "timerEvent()";

  QWebView::timerEvent( event );

  mTapTimer.stop();

  QWebFrame *frame = page()->mainFrame();
  double lat = frame->evaluateJavaScript( "map.get_center().lat()" ).toDouble();
  double lng = frame->evaluateJavaScript( "map.get_center().lng()" ).toDouble();

  setCenter( lat, lng );

  update();
}

/*
 * setCenter
 */
void MapWidget::setCenter( double latitude, double longitude )
{
  QString code = "map.set_center(new google.maps.LatLng(%1, %2));";
  QWebFrame *frame = page()->mainFrame();
  frame->evaluateJavaScript( code.arg( latitude ).arg( longitude ) );
}

/*
 * mousePressEvent
 */
void MapWidget::mousePressEvent( QMouseEvent* event )
{
  mPressed = true;
  mPressPos = event->pos();
  mDragPos = event->pos();

  mTapTimer.stop();
  mTapTimer.start( 700, this );

  QWebView::mousePressEvent( event );
}

/*
 * mouseReleaseEvent
 */
void MapWidget::mouseReleaseEvent( QMouseEvent* event )
{
  mPressed = false;

  mTapTimer.stop();

  event->accept();
  update();

  QWebView::mouseReleaseEvent( event );
}

/*
 * mouseMoveEvent
 */
void MapWidget::mouseMoveEvent( QMouseEvent* event )
{
  if( !mPressed ) {
    QWebView::mouseMoveEvent( event );
    return;
  }

  mDragPos = event->pos();
  update();
}

} // namespace ptui
