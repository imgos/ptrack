#include <ptrackUi/MapWidget.h>

#include <ptrackUi/MapPage.h>

namespace ptui {

const char* MapWidget::kHtml = "<html><head><script type=\"text/javascript\" " \
    "src=\"http://maps.google.com/maps/api/js?sensor=false\"></script>" \
    "<script  type=\"text/javascript\">" \
    "var map; function init(lat, lng) { "\
    "map = new google.maps.Map(document.getElementById(\"map_canvas\"), " \
    "{ zoom: 5, draggable: true, center: new google.maps.LatLng(lat, lng), " \
    "disableDefaultUI: true, mapTypeId: google.maps.MapTypeId.ROADMAP, " \
    "scrollwheel: true, navigationControl: true, disableDoubleClickZoom: false });" \
    "} </script>" \
    "</head><body style=\"margin:0px; padding:0px;\">" \
    "<div id=\"map_canvas\" style=\"width:100%; height:100%\"></div>" \
    "</body></html>";

/*
 * MapWidget
 */
MapWidget::MapWidget( QWidget* parent )
 : QWebView( parent ),
   mPressed( false )
{
  setMouseTracking( true );

  setPage( new MapPage );

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
  QWebView::timerEvent( event );

  QWebFrame *frame = page()->mainFrame();
  double lat = frame->evaluateJavaScript( "map.getCenter().lat()" ).toDouble();
  double lng = frame->evaluateJavaScript( "map.getCenter().lng()" ).toDouble();

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
  event->ignore();
  QWebView::mousePressEvent( event );

  mPressed = true;
  mPressPos = event->pos();
  mDragPos = event->pos();
}

/*
 * mouseReleaseEvent
 */
void MapWidget::mouseReleaseEvent( QMouseEvent* event )
{
  event->ignore();
  QWebView::mouseReleaseEvent( event );

  mPressed = false;

  update();
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

  event->ignore();
  QWebView::mouseMoveEvent( event );

  mDragPos = event->pos();
  update();
}

} // namespace ptui
