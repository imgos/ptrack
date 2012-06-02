project( ptrackData )

set( sourceFiles
  ActivityDb.cpp
  PTrackPreferencesData.cpp
  import/GenericImport.cpp
  import/SportTracksImport.cpp
)

set( headerFiles
  ActivityDb.h
  PTrackDataMacros.h
  PTrackPreferencesData.h
  import/GenericImport.h
  import/SportTracksImport.h
)

add_definitions(
  -DBUILDING_DLL
  -DBOOST_ALL_DYN_LINK
  -DBOOST_FILESYSTEM_VERSION=3
)

find_package( Boost COMPONENTS system filesystem REQUIRED )
find_package( SQLITE3 REQUIRED )

set( QT_USE_QT3SUPPORT FALSE )
find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${QT_INCLUDES}
  ${Boost_INCLUDE_DIR}
  ${SQLITE3_INCLUDE_DIR}
)

source_group( [*.h] FILES ${headerFiles} )
source_group( [*.cpp] FILES ${sourceFiles} )

add_library( ${PROJECT_NAME} SHARED
  ${sourceFiles}
  ${headerFiles}
)

target_link_libraries( ${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${Boost_LIBRARIES}
  ${SQLITE3_LIBRARIES}
)
