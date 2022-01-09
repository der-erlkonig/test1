aux_source_directory(. MEMORY)

add_library(memory SHARED)
set_target_properties(memory PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_include_directories(memory PRIVATE ${PROJECT_SOURCE_DIR}/include/memory)
target_sources(memory PRIVATE ${MEMORY})

add_library(memory_static STATIC)
target_include_directories(memory_static PRIVATE ${PROJECT_SOURCE_DIR}/include/memory)
target_sources(memory_static PRIVATE ${MEMORY})
set_target_properties(memory_static PROPERTIES OUTPUT_NAME "memory")

install(TARGETS memory memory_static
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)