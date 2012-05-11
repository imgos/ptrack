#ifndef PTrackUi_h
#define PTrackUi_h

#include <ptrackUi/PTrackUiMacros.h>

#include <QMainWindow>

#include <boost/scoped_ptr.hpp>

namespace Ui { class PTrackUiBase; }


class PTUI_API PTrackUi : public QMainWindow
{
  Q_OBJECT

public:
  PTrackUi();

private:
  boost::scoped_ptr< Ui::PTrackUiBase > mUi;
};

#endif
