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

  connect( this, SIGNAL( loadFinished( bool ) ), SLOT( htmlLoadFinished( bool ) ) );
}

/*
 * htmlLoadFinished
 */
void MapWidget::htmlLoadFinished( bool success )
{
  qDebug() << "htmlLoadFinished( bool )";

  if( success ) {
    triggerInitMap();
  }
}

/*
 * triggerInitMap
 */
void MapWidget::triggerInitMap()
{
  qDebug() << "triggerInitMap()";

  QString code = "init(37.6970, -91.8096)";
  QWebFrame* frame = page()->mainFrame();
  frame->evaluateJavaScript( code );

  // default start of map is just centered on USA
  setBounds( 24.52, -124.77, 49.38, -66.95 );
}

/*
 * setCenter
 */
void MapWidget::setCenter( double latitude, double longitude )
{
  QString code = "map.setCenter( new google.maps.LatLng( %1, %2 ) );";
  QWebFrame* frame = page()->mainFrame();
  frame->evaluateJavaScript( code.arg( latitude ).arg( longitude ) );
}

/*
 * setBounds
 */
void MapWidget::setBounds( double latSW, double lonSW, double latNE, double lonNE )
{
  QStringList code = QStringList()
                     << "var bounds = new google.maps.LatLngBounds("
                     << "               new google.maps.LatLng( %1, %2 ),"
                     << "               new google.maps.LatLng( %3, %4 ) );"
                     << "map.fitBounds( bounds );";
  QWebFrame* frame = page()->mainFrame();
  frame->evaluateJavaScript( code.join( "\n" ).arg( latSW ).arg( lonSW ).arg( latNE ).arg( lonNE ) );
}

} // namespace ptui
