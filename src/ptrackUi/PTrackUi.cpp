#include <ptrackUi/PTrackUi.h>

#include <ptrackUi/ui_PTrackUiBase.h>

#include <ptrackUi/PTrackPreferencesDialog.h>

namespace ptui {

PTrackUi::PTrackUi()
 : QMainWindow(),
   mUi( new Ui::PTrackUiBase )
{
  mUi->setupUi( this );

  connect( mUi->mPreferencesAction, SIGNAL( triggered() ), this, SLOT( openPreferences() ) );
}

void PTrackUi::openPreferences()
{
  boost::scoped_ptr< PTrackPreferencesDialog > prefs( new PTrackPreferencesDialog );
  prefs->exec();
}

} //namespace ptui
