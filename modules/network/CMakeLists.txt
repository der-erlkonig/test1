aux_source_directory(. ONVIF_NETWORK)

add_library(network SHARED)
target_include_directories(network PRIVATE ${PROJECT_SOURCE_DIR}/include/network)
target_include_directories(network PRIVATE ${PROJECT_SOURCE_DIR}/include/cJSON)
set_target_properties(network PROPERTIES VERSION 0.0.2 SOVERSION 0 PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/network/network.h)
target_sources(network PRIVATE ${ONVIF_NETWORK})

install(TARGETS network
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib
		PUBLIC_HEADER DESTINATION onvif/include/network)