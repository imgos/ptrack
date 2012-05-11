#ifndef PTrackPreferencesDialog_h
#define PTrackPreferencesDialog_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackUi/ui_PTrackPreferencesDialogBase.h>

#include <boost/scoped_ptr.hpp>

namespace ptui {

class PTUI_API PTrackPreferencesDialog : public QDialog
{
  Q_OBJECT

public:
  PTrackPreferencesDialog();

private:
  boost::scoped_ptr< Ui::PTrackPreferencesDialogBase > mUi;
};

} // namespace ptui

#endif
