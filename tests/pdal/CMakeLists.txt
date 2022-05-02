set(TARGET test_pdalc)

find_package(PDAL REQUIRED CONFIG)

set(CONFIGS )

IF (CONDA_BUILD)
	set(SOURCES
		main_conda.c
		test_pdalc_config.c
		test_pdalc_utils.c
	)
ELSE()
	set(SOURCES
		main.c
		test_pdalc_config.c
		test_pdalc_utils.c
	)
ENDIF()

set(HEADERS 
	test_pdalc_utils.h
)

set(DEPENDENCIES 
	${PDAL_LIBRARIES}
	pdalc
)

if (NOT CONDA_BUILD)
	set(TESTS
		test_pdalc_pipeline
		test_pdalc_pointlayout
		test_pdalc_pointview
		test_pdalc_pointviewiterator
	)

	foreach(TEST ${TESTS})
		configure_file(${TEST}.c.in ${CMAKE_CURRENT_SOURCE_DIR}/${TEST}.c)

		list(APPEND CONFIGS ${TEST}.c.in)
		list(APPEND SOURCES ${TEST}.c)
	endforeach()

	source_group("Config Files" FILES ${CONFIGS})
ENDIF()

include_directories(
	${CMAKE_SOURCE_DIR}/source
	${PDAL_INCLUDE_DIRS}
)

# Add definition if building debug with vcpkg - PDAL_PLUGIN_INSTALL_PATH points to release binaries
string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPERCASE)
if (BUILD_TYPE_UPPERCASE STREQUAL "DEBUG" AND VCPKG_TARGET_TRIPLET)
	add_definitions(-DUSING_VCPKG_DEBUG)
endif()

add_executable(${TARGET} ${SOURCES} ${HEADERS} ${CONFIG})
set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(${TARGET} ${DEPENDENCIES})
add_test(NAME ${TARGET} COMMAND ${TARGET})

install(TARGETS ${TARGET}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)

set(TARGET test_pdalc)