/*
 *
 */

#include <ptrackUi/PTrackUi.h>

#include <QApplication>
#include <QNetworkProxyFactory>

int main( int argc, char** argv )
{
  QNetworkProxyFactory::setUseSystemConfiguration( true );

  QApplication a( argc, argv );

  ptui::PTrackUi* pt = new ptui::PTrackUi();
  pt->show();

  return a.exec();
}
