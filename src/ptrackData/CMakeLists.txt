project( ptrackData )

file( GLOB sourceFiles *.cpp )
file( GLOB headerFiles *.h )

add_definitions(
  -DBUILDING_DLL
)

find_package( Boost REQUIRED )
find_package( SQLITE3 REQUIRED )

set( QT_USE_QT3SUPPORT FALSE )
find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${QT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
  ${SQLITE3_INCLUDE_DIR}
)

add_library( ${PROJECT_NAME} SHARED
  ${sourceFiles}
  ${headerFiles}
)

target_link_libraries( ${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${SQLITE3_LIBRARIES}
)
