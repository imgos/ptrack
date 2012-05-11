project( ptrackUi )

file( GLOB headerFiles *.h )
file( GLOB sourceFiles *.cpp )
file( GLOB uiFiles *.ui )

find_package( Boost REQUIRED )

set( QT_USE_QT3SUPPORT FALSE )
find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

add_definitions(
  -DBUILDING_DLL
)

QT4_WRAP_UI( uicHeaders ${uiFiles} )
QT4_WRAP_CPP( mocSources ${headerFiles} )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${QT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
)

add_library( ${PROJECT_NAME} SHARED
  ${sourceFiles}
  ${mocSources}
  ${uicHeaders}
)

target_link_libraries( ${PROJECT_NAME}
  ${QT_LIBRARIES}
)
