/*
 *
 */

#include <ptrackUi/PTrackUi.h>

#include <QApplication>

int main( int argc, char** argv )
{
  QApplication a( argc, argv );

  PTrackUi* pt = new PTrackUi();
  pt->show();

  return a.exec();
}
