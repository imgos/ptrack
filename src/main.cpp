/*
 *
 */

#include <ptrackUi/PTrackUi.h>

#include <QApplication>

int main( int argc, char** argv )
{
  QApplication a( argc, argv );

  ptui::PTrackUi* pt = new ptui::PTrackUi();
  pt->show();

  return a.exec();
}
