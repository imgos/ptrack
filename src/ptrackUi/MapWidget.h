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

};

} // namespace ptui

#endif
