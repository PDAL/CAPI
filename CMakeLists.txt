# Top-level CMake configuration file for pdal-c

cmake_minimum_required(VERSION 2.8)

project(pdal-c C CXX)

# Use C11 and C++11 standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Install to the build directory
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE STRING "CMake install prefix" FORCE)

# Use "d" suffix for debug builds
# Do not use a suffix for RelWithDebInfo
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "CMake debug suffix")
set(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "CMake RelWithDebInfo suffix")

include_directories("${CMAKE_SOURCE_DIR}/source")
add_subdirectory("source/pdal/capi")

include(CTest)
add_subdirectory("tests/pdal/capi")