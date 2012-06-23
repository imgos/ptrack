#ifndef ptui_PTrackAboutDialog_h
#define ptui_PTrackAboutDialog_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackUi/ui_PTrackAboutDialogBase.h>

#include <boost/scoped_ptr.hpp>

namespace ptui {

class PTUI_API PTrackAboutDialog : public QDialog
{
  Q_OBJECT

public:
  PTrackAboutDialog( QWidget* parent = 0 );
  PTrackAboutDialog( const QString& databaseVersion, QWidget* parent = 0 );

protected:
  void init( const QString& databaseVersion = "" );

private:
  boost::scoped_ptr< ::Ui::PTrackAboutDialogBase > mUi;
};

} // namespace ptui

#endif
