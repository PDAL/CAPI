# Top-level CMake configuration file for pdal-c

cmake_minimum_required(VERSION 3.9)

project(pdal-c C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

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
set(PDALC_ENABLE_CODE_COVERAGE ON CACHE BOOL "Enable code coverage calculation")
set(PDALC_ENABLE_DOCS ON CACHE BOOL "Enable documentation generation")
set(PDALC_ENABLE_TESTS ON CACHE BOOL "Enable pdal-c tests")
set(PDALC_GCC_PARAM_GGC_MIN_HEAPSIZE "131072" CACHE STRING "GCC garbage collection minimum heap size")

include(ObtainProjectVersion)
include_directories("${CMAKE_SOURCE_DIR}/source")

if(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(--param ggc-min-heapsize=${PDALC_GCC_PARAM_GGC_MIN_HEAPSIZE})

	if(PDALC_ENABLE_CODE_COVERAGE AND PDALC_ENABLE_TESTS)
		message(STATUS "Enabled code coverage analysis")
		include(CodeCoverage)
		APPEND_COVERAGE_COMPILER_FLAGS()
		set(COVERAGE_EXCLUDES
			'build/*'
			'cmake/*'
			'tests/pdal/*'
			'/usr/include/*'
		)
	endif()
endif()

add_subdirectory("source/pdal")

if(PDALC_ENABLE_DOCS)
	add_subdirectory("doc")
endif()

if(PDALC_ENABLE_TESTS)
	include(CTest)
	add_subdirectory("tests/data")
	add_subdirectory("tests/pdal")
endif()