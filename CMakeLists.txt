cmake_minimum_required(VERSION 3.5)
project(datastructures-workout)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
include(cmake/install-gtest.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/googletest/install/include)

enable_testing()
add_subdirectory(tests)
