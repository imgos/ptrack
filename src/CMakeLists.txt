project( ptrack )

cmake_minimum_required( VERSION 2.6 )

if( UNIX OR MINGW )
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
else()
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
endif()

add_subdirectory( ptrackData )
add_subdirectory( ptrackUi )

file( GLOB srcFiles *.cpp )

find_package( Boost REQUIRED )

set( QT_USE_QT3SUPPORT FALSE )
find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${Boost_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
)

add_executable( ${PROJECT_NAME}
  ${srcFiles}
)

target_link_libraries( ${PROJECT_NAME}
  ${QT_LIBRARIES}
  ptrackUi
)
