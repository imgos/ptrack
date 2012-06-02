project( ptrackUi )

set( headerFiles
  MapPage.h
  MapWidget.h
  PTrackAboutDialog.h
  PTrackPreferencesDialog.h
  PTrackUi.h
  PTrackUiMacros.h
)

set( sourceFiles
  MapPage.cpp
  MapWidget.cpp
  PTrackAboutDialog.cpp
  PTrackPreferencesDialog.cpp
  PTrackUi.cpp
)

set( uiFiles
  PTrackAboutDialogBase.ui
  PTrackPreferencesDialogBase.ui
  PTrackUiBase.ui
)

set( resourceFiles
  ../../images/ptrack.qrc
)

add_definitions(
  -DBUILDING_DLL
)

find_package( Boost REQUIRED )
find_package( SQLITE3 REQUIRED )

set( QT_USE_QT3SUPPORT FALSE )
set( QT_USE_QTWEBKIT TRUE )
find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

QT4_WRAP_UI( uicHeaders ${uiFiles} )
QT4_WRAP_CPP( mocSources ${headerFiles} )
QT4_ADD_RESOURCES( rccSource ${resourceFiles} )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${QT_INCLUDES}
  ${Boost_INCLUDE_DIR}
  ${SQLITE3_INCLUDE_DIR}
)

source_group( [*.h] FILES ${headerFiles} )
source_group( [*.cpp] FILES ${sourceFiles} )
source_group( [*.ui] FILES ${uiFiles} )
source_group( [resources] FILES ${resourceFiles} )
source_group( Generated\[*.h] FILES ${uicHeaders} )
source_group( Generated\[*.cxx] FILES ${mocSources} ${rccSource} )
source_group( Generated\[cmake] REGULAR_EXPRESSION moc_.*\.rule$ )

add_library( ${PROJECT_NAME} SHARED
  ${sourceFiles}
  ${headerFiles}
  ${mocSources}
  ${uicHeaders}
  ${rccSource}
)

target_link_libraries( ${PROJECT_NAME}
  ptrackData
  ${QT_LIBRARIES}
  ${QT_QTWEBKIT_LIBRARY}
)
