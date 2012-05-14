project( ptrackUi )

file( GLOB headerFiles *.h )
file( GLOB sourceFiles *.cpp )
file( GLOB uiFiles *.ui )

add_definitions(
  -DBUILDING_DLL
)

find_package( Boost REQUIRED )
find_package( SQLITE3 REQUIRED )

set( QT_USE_QT3SUPPORT FALSE )
set( QT_USE_WEBKIT TRUE )
find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

QT4_WRAP_UI( uicHeaders ${uiFiles} )
QT4_WRAP_CPP( mocSources ${headerFiles} )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${QT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
  ${SQLITE3_INCLUDE_DIR}
)

add_library( ${PROJECT_NAME} SHARED
  ${sourceFiles}
  ${headerFiles}
  ${mocSources}
)

target_link_libraries( ${PROJECT_NAME}
  ptrackData
  ${QT_LIBRARIES}
  ${QT_QTWEBKIT_LIBRARY}
)
