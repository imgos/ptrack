#ifndef ptui_PTrackPreferencesDialog_h
#define ptui_PTrackPreferencesDialog_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackUi/ui_PTrackPreferencesDialogBase.h>

#include <boost/scoped_ptr.hpp>

namespace ptui {

class PTUI_API PTrackPreferencesDialog : public QDialog
{
  Q_OBJECT

public:
  PTrackPreferencesDialog( QWidget* parent = 0 );

protected Q_SLOTS:
  virtual void accept();

  void dbPathButtonClicked();

Q_SIGNALS:
  void prefsChanged();

private:
  boost::scoped_ptr< Ui::PTrackPreferencesDialogBase > mUi;
};

} // namespace ptui

#endif
