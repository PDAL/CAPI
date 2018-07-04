# CMake script to derive project version from repository info

find_package(Git)

# Use `git describe` to derive patch and build info
if(GIT_FOUND)
	execute_process(COMMAND "${GIT_EXECUTABLE}" "describe" "--tags" "--long"
		OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE GIT_DESCRIBE_OUTPUT
		ERROR_STRIP_TRAILING_WHITESPACE ERROR_VARIABLE GIT_DESCRIBE_ERROR)

	# We use tags with the three version numbers
	# Use the remainder of the `git describe` output for the build ID
	if(GIT_DESCRIBE_OUTPUT MATCHES "^([0-9]+)\\.([0-9]+)\\.([0-9]+)-([0-9]+)-g([a-f0-9]+)$")
		string(REGEX REPLACE "([0-9]+).*" "\\1" MAJOR_VERSION ${GIT_DESCRIBE_OUTPUT})
		string(REGEX REPLACE "([0-9]+)\\.([0-9]+).*" "\\2" MINOR_VERSION ${GIT_DESCRIBE_OUTPUT})
		string(REGEX REPLACE "([0-9]+)\\.([0-9]+)\\.([0-9]+).*" "\\3" PATCH_VERSION ${GIT_DESCRIBE_OUTPUT})
		string(REGEX REPLACE ".*-(.*)-.*" "\\1" COMMIT_COUNT ${GIT_DESCRIBE_OUTPUT})
		string(REGEX REPLACE ".*-g(.*)" "\\1" COMMIT_ID ${GIT_DESCRIBE_OUTPUT})
		set(BUILD_ID "build ${COMMIT_COUNT} (${COMMIT_ID})")
	else()
	message(WARNING "Could not derive version and build ID: 'git describe' command output was \"${GIT_DESCRIBE_OUTPUT}\" - ${GIT_DESCRIBE_ERROR}")
	endif()

	# Suffix BUILD_ID with " (with uncommitted changes)" if `git status --porcelain` does not return an empty string
	execute_process(COMMAND "${GIT_EXECUTABLE}" "status" "--porcelain"
		OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE GIT_STATUS_OUTPUT)

	if(NOT "${GIT_STATUS_OUTPUT}" STREQUAL "")
		string(APPEND BUILD_ID " with uncommitted changes")
	endif()
else()
	message(WARNING "Could not derive version and build ID: Git not found")
endif()

set(${PROJECT_NAME}_VERSION_MAJOR ${MAJOR_VERSION})
set(${PROJECT_NAME}_VERSION_MINOR ${MINOR_VERSION})
set(${PROJECT_NAME}_VERSION_PATCH ${PATCH_VERSION})
set(${PROJECT_NAME}_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

string (TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPERCASE)
set(${PROJECT_NAME_UPPERCASE}_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(${PROJECT_NAME_UPPERCASE}_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
set(${PROJECT_NAME_UPPERCASE}_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH})
set(${PROJECT_NAME_UPPERCASE}_VERSION ${${PROJECT_NAME}_VERSION})
