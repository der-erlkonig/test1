aux_source_directory(. ONVIF_NETWORK)

add_library(network SHARED)
target_include_directories(network PRIVATE ${PROJECT_SOURCE_DIR}/include/network)
target_include_directories(network PRIVATE ${PROJECT_SOURCE_DIR}/include/cJSON)
set_target_properties(network PROPERTIES VERSION 0.0.2 SOVERSION 0 PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/network/network.h)
target_sources(network PRIVATE ${ONVIF_NETWORK})

add_library(network_static STATIC)
target_include_directories(network_static PRIVATE ${PROJECT_SOURCE_DIR}/include/network)
target_include_directories(network_static PRIVATE ${PROJECT_SOURCE_DIR}/include/cJSON)
target_sources(network_static PRIVATE ${ONVIF_NETWORK})
set_target_properties(network_static PROPERTIES OUTPUT_NAME "network")

install(TARGETS network network_static
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib
		PUBLIC_HEADER DESTINATION onvif/include/network)