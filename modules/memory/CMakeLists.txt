aux_source_directory(. MEMORY)

add_library(memory SHARED)
set_target_properties(memory PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_sources(memory PRIVATE ${MEMORY})

install(TARGETS memory
		LIBRARY DESTINATION onvif/lib)