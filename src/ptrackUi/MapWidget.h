#ifndef MapWidget_h
#define MapWidget_h

#include <ptrackUi/PTrackUiMacros.h>

#include <QtNetwork/QNetworkAccessManager>
#include <QtWebKit/QtWebKit>

#include <boost/shared_ptr.hpp>

namespace ptui {

class PTUI_API MapWidget : public QWebView
{
  Q_OBJECT

public:
  MapWidget( QWidget* parent = 0 );

protected:
  void mousePressEvent( QMouseEvent* event );
  void mouseReleaseEvent( QMouseEvent* event );
  void mouseMoveEvent( QMouseEvent* event );

private Q_SLOTS:
  void triggerLoading();

private:
  boost::shared_ptr< QNetworkAccessManager > mNetManager;

  bool mPressed;
  QPoint mPressPos;
  QPoint mDragPos;

  static const char* kHtml;
};

} // namespace ptui

#endif
