cmake_minimum_required (VERSION 2.6)
project (solution)

set( CMAKE_CXX_FLAGS "-std=c++17" )

include_directories ("${PROJECT_SOURCE_DIR}")
add_subdirectory (unit_tests)

add_library(Solution solution.cpp)
