set(TARGET test_pdal_c)

configure_file(PipelineTest.c.in ${CMAKE_CURRENT_SOURCE_DIR}/PipelineTest.c)
configure_file(PointViewTest.c.in ${CMAKE_CURRENT_SOURCE_DIR}/PointViewTest.c)
configure_file(PointViewCollectionTest.c.in ${CMAKE_CURRENT_SOURCE_DIR}/PointViewCollectionTest.c)

set(CONFIG
	PipelineTest.c.in
	PointViewCollectionTest.c.in
	PointViewTest.c.in
)

source_group("Config Files" FILES ${CONFIG})

set(SOURCES
	main.c
	PipelineTest.c
	PointViewCollectionTest.c
	PointViewTest.c
)

set(HEADERS )

set(DEPENDENCIES pdal_c)

include_directories(${CMAKE_SOURCE_DIR}/source)

add_executable(${TARGET} ${SOURCES} ${HEADERS} ${CONFIG})
set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(${TARGET} ${DEPENDENCIES})
add_test(NAME ${TARGET} COMMAND ${TARGET})

install(TARGETS ${TARGET}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)
