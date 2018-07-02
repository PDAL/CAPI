set(TARGET pdal_c)

find_package(PDAL REQUIRED CONFIG)
message(STATUS "Found PDAL ${PDAL_VERSION}")

set(SOURCES
	DimType.cpp
	Pipeline.cpp
	PointLayout.cpp
	PointView.cpp
	PointViewIterator.cpp
)

set(HEADERS
	Defines.h
	DimType.h
	Forward.h
	Pipeline.h
	PointLayout.h
	PointView.h
	PointViewIterator.h
)

set(DEPENDENCIES
	${PDAL_LIBRARIES}
)

link_directories(
	${PDAL_LIBRARY_DIRS}
)

include_directories(
	${PDAL_INCLUDE_DIRS}
)

add_definitions(${PDAL_DEFINITIONS})

add_library(${TARGET} SHARED ${SOURCES} ${HEADERS})

string(TOUPPER "${TARGET}_BUILD_DLL" BUILD_SYMBOL)

set_target_properties(${TARGET} PROPERTIES
	DEFINE_SYMBOL ${BUILD_SYMBOL}
	VERSION ${PDAL_VERSION}
	SOVERSION ${PDAL_VERSION}
)

# Measure code coverage on gcc
if(CMAKE_COMPILER_IS_GNUCXX AND PDALC_ENABLE_CODE_COVERAGE)
	SETUP_TARGET_FOR_COVERAGE(
		NAME coverage_${TARGET}
		EXECUTABLE test_${TARGET}
		DEPENDENCIES test_${TARGET}
	)
endif()

target_link_libraries(${TARGET} ${DEPENDENCIES})

install(TARGETS ${TARGET}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)

file(RELATIVE_PATH ${TARGET}_PATH ${CMAKE_SOURCE_DIR}/source ${CMAKE_CURRENT_SOURCE_DIR})
install(FILES ${HEADERS} DESTINATION include/${${TARGET}_PATH})
