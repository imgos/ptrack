#ifndef MapWidget_h
#define MapWidget_h

#include <ptrackUi/PTrackUiMacros.h>

#include <QtWebKit/QtWebKit>

namespace ptui {

class PTUI_API MapWidget : public QWebView
{
  Q_OBJECT

public:
  MapWidget( QWidget* parent = 0 );

  void setCenter( double latitude, double longitude );
  void setBounds( double latSW, double lonSW, double latNE, double lonNE );

private Q_SLOTS:
  void triggerInitMap();
  void htmlLoadFinished( bool success );

private:
  bool mPressed;
  QPoint mPressPos;
  QPoint mDragPos;

  static const char* kHtml;
};

} // namespace ptui

#endif
