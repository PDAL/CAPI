# Top-level CMake configuration file for pdal-c

cmake_minimum_required(VERSION 2.8)

project(pdal-c C CXX)

# Use C11 and C++11 standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("${CMAKE_SOURCE_DIR}/source")
add_subdirectory("source/pdal/capi")

