#include <ptrackUi/MapWidget.h>

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
   mNetManager( new QNetworkAccessManager( this ) )
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
  QString code = "init(37.6970,  -91.8096)";
  QWebFrame *frame = page()->mainFrame();
  frame->evaluateJavaScript( code );
}

/*
 * mousePressEvent
 */
void MapWidget::mousePressEvent( QMouseEvent* event )
{
  mPressed = true;
  mPressPos = event->pos();
  mDragPos = event->pos();
  QWebView::mousePressEvent( event );
}

/*
 * mouseReleaseEvent
 */
void MapWidget::mouseReleaseEvent( QMouseEvent* event )
{
  mPressed = false;
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
