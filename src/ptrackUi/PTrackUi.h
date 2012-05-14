#ifndef PTrackUi_h
#define PTrackUi_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackUi/ui_PTrackUiBase.h>

#include <ptrackData/ActivityDb.h>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

class QCloseEvent;


namespace ptui {

class PTUI_API PTrackUi : public QMainWindow
{
  Q_OBJECT

public:
  PTrackUi( QWidget* parent = 0 );

  void closeEvent( QCloseEvent* e );

protected Q_SLOTS:
  void openPreferences();

private:
  boost::scoped_ptr< Ui::PTrackUiBase > mUi;

  boost::shared_ptr< ptdata::ActivityDb > mDb;
};

} //namespace ptui

#endif
