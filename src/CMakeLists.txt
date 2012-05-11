project( ptrack )

cmake_minimum_required( VERSION 2.6 )

if( UNIX OR MINGW )
  set( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib )
else()
  set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
  set( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE} )
endif()

add_subdirectory( ptrackUi )

file( GLOB srcFiles *.cpp )

set( QT_USE_QT3SUPPORT FALSE )
find_package( Qt4 REQUIRED )

include( ${QT_USE_FILE} )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${QT_INCLUDE_DIR}
)

add_executable( ${PROJECT_NAME}
  ${srcFiles}
)

target_link_libraries( ${PROJECT_NAME}
  ${QT_LIBRARIES}
  ptrackUi
)
