#ifndef MapPage_h
#define MapPage_h

#include <QtWebKit/QWebPage>

namespace ptui {

class MapPage : public QWebPage
{
protected:
  virtual QString userAgentForUrl( const QUrl& url ) const;
};

} //namespace ptui

#endif
