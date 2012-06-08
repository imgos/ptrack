#ifndef ptui_MapPage_h
#define ptui_MapPage_h

#include <QtWebKit/QWebPage>

namespace ptui {

class MapPage : public QWebPage
{
protected:
  virtual QString userAgentForUrl( const QUrl& url ) const;
};

} //namespace ptui

#endif
