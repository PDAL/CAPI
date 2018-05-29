set(PIPELINES
	stats.json
)

foreach(PIPELINE ${PIPELINES})
	configure_file(${PIPELINE}.in ${CMAKE_BINARY_DIR}/data/${PIPELINE})
endforeach()

