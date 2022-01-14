aux_source_directory(. IO)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/include/io)

add_library(config_io SHARED)
set_target_properties(config_io PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_include_directories(config_io PRIVATE ${INC_ROOT})
target_sources(config_io PRIVATE ${IO})

add_library(config_io_static STATIC)
set_target_properties(config_io_static PROPERTIES OUTPUT_NAME "config_io")
target_include_directories(config_io_static PRIVATE ${INC_ROOT})
target_sources(config_io_static PRIVATE ${IO})

install(TARGETS config_io config_io_static
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)