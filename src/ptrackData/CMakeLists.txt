project( ptrackData )

file( GLOB sourceFiles *.cpp )

add_definitions(
  -DBUILDING_DLL
)

find_package( Boost REQUIRED )

set( QT_USE_QT3SUPPORT FALSE )
find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${QT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
)

add_library( ${PROJECT_NAME} SHARED
  ${sourceFiles}
  ${QT_LIBRARIES}
)
