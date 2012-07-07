#ifndef ptui_ImportDialog_h
#define ptui_ImportDialog_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackUi/ui_ImportDialogBase.h>

#include <ptrackData/ActivityDb.h>

#include <boost/scoped_ptr.hpp>

namespace ptui {

class PTUI_API ImportDialog : public QDialog
{
  Q_OBJECT

public:
  ImportDialog( QWidget* parent = 0 );

private:
  boost::scoped_ptr< Ui::ImportDialogBase > mUi;
};

} // namespace ptui

#endif
