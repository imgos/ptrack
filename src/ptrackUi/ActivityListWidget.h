#ifndef ptui_ActivityListWidget_h
#define ptui_ActivityListWidget_h

#include <ptrackUi/PTrackUiMacros.h>

#include <ptrackData/ActivityDb.h>

#include <QListWidget>

#include <vector>

namespace ptui {

class PTUI_API ActivityListWidget : public QListWidget
{
  Q_OBJECT

public:
  ActivityListWidget( QWidget* parent = 0 );
  virtual ~ActivityListWidget();

  void populateFromActivityVector( std::vector< ptdata::ActivityDb::Activity > activities );

};

} // namespace ptui

#endif
