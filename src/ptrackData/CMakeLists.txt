project( ptrackData )

file( GLOB sourceFiles *.cpp )

add_definitions(
  -DBUILDING_DLL
)

find_package( Boost REQUIRED )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${Boost_INCLUDE_DIR}
)

add_library( ${PROJECT_NAME} SHARED
  ${sourceFiles}
)
