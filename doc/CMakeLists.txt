# CMake configuration file for Keryx documentation

find_package(Doxygen)

if (DOXYGEN_FOUND)
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in" "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")

	add_custom_target( "${PROJECT_NAME}_doxygen" ALL
		COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM )

	install(DIRECTORY doxygen DESTINATION doc)
else()
	message(STATUS "Could not generate ${PROJECT_NAME} API help documentation: Doxygen not found")
endif()