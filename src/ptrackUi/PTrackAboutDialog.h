#ifndef PTrackAboutDialog_h
#define PTrackAboutDialog_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackUi/ui_PTrackAboutDialogBase.h>

#include <boost/scoped_ptr.hpp>

namespace ptui {

class PTUI_API PTrackAboutDialog : public QDialog
{
  Q_OBJECT

public:
  PTrackAboutDialog( QWidget* parent = 0 );

private:
  boost::scoped_ptr< Ui::PTrackAboutDialogBase > mUi;
};

} // namespace ptui

#endif
