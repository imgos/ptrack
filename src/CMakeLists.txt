project( ptrack )

cmake_minimum_required( VERSION 2.6 )

set( CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/CMakeModules
)

if( UNIX OR MINGW )
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
else()
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
endif()

set( CMAKE_DEBUG_POSTFIX "d" )

add_subdirectory( ptrackData )
add_subdirectory( ptrackUi )

file( GLOB srcFiles *.cpp )

find_package( Boost REQUIRED )

set( QT_USE_QT3SUPPORT FALSE )
set( QT_USE_QTNETWORK TRUE )
find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${Boost_INCLUDE_DIR}
  ${QT_INCLUDES}
)

if( WIN32 )
  set( typeId WIN32 )
  set( winIconResource winIcon.rc )
elseif( APPLE )
  set( typeId MACOSX_BUNDLE )
endif()

source_group( [cpp] FILES ${srcFiles} ${winIconResource} )

add_executable( ${PROJECT_NAME} ${typeId} ${winIconResource}
  ${srcFiles}
)

set_property( TARGET ${PROJECT_NAME} PROPERTY DEBUG_POSTFIX d )

target_link_libraries( ${PROJECT_NAME}
  ${QT_QTMAIN_LIBRARY}
  ${QT_LIBRARIES}
  ptrackUi
)
