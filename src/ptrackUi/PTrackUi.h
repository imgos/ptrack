#ifndef PTrackUi_h
#define PTrackUi_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackUi/ui_PTrackUiBase.h>

#include <boost/scoped_ptr.hpp>


namespace ptui {

class PTUI_API PTrackUi : public QMainWindow
{
  Q_OBJECT

public:
  PTrackUi();

protected Q_SLOTS:
  void openPreferences();

private:
  boost::scoped_ptr< Ui::PTrackUiBase > mUi;
};

} //namespace ptui

#endif
