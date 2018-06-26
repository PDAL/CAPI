set(TARGET test_pdal_c)

set(CONFIGS )
set(SOURCES main.c)
set(HEADERS )
set(DEPENDENCIES pdal_c)

set(TESTS
	PipelineTest
	PointLayoutTest
	PointViewIteratorTest
	PointViewTest
)

foreach(TEST ${TESTS})
	configure_file(${TEST}.c.in ${CMAKE_CURRENT_SOURCE_DIR}/${TEST}.c)

	list(APPEND CONFIGS ${TEST}.c.in)
	list(APPEND SOURCES ${TEST}.c)
endforeach()

source_group("Config Files" FILES ${CONFIGS})
include_directories(${CMAKE_SOURCE_DIR}/source)

add_executable(${TARGET} ${SOURCES} ${HEADERS} ${CONFIG})
set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(${TARGET} ${DEPENDENCIES})
add_test(NAME ${TARGET} COMMAND ${TARGET})

install(TARGETS ${TARGET}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)
