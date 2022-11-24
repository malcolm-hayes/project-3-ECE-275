find_package( LEMON REQUIRED )

set( target graphsearch )

file(GLOB src CONFIGURE_DEPENDS  "${CMAKE_SOURCE_DIR}/src/*.cpp")
message(STATUS "Got the following files for your executable:")
foreach(s ${src})
  message(STATUS "   ${s}")
endforeach()

add_executable( ${target} ${src} )

target_include_directories( ${target} SYSTEM PUBLIC
  ${LEMON_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS} )
target_link_libraries( ${target} PUBLIC
  ${LEMON_LIBRARIES}
  ${Boost_LIBRARIES} )
