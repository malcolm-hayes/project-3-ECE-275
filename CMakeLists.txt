cmake_minimum_required( VERSION 3.8 )

project( GraphSearch CXX )

set( CMAKE_CXX_STANDARD 17 )

# Enable all warnings and extra warnings
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options( -Wall -Wextra )
endif()

if ( NOT TESTING_ONLY )
  add_subdirectory( src )
endif()

if ( TESTING OR TESTING_ONLY )
  add_compile_options ( -Werror )
  enable_testing()
  add_subdirectory( tester )
endif()
