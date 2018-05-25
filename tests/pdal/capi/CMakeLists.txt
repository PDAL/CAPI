set(TARGET test_pdal_c)

set(SOURCES
	main.c
	PipelineTest.c
	PointViewCollectionTest.c
	)

set(HEADERS )

set(DEPENDENCIES pdal_c)

include_directories(${CMAKE_SOURCE_DIR}/source)

add_executable(${TARGET} ${SOURCES} ${HEADERS})
set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(${TARGET} ${DEPENDENCIES})
add_test(NAME ${TARGET} COMMAND ${TARGET})

install(TARGETS ${TARGET}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)
