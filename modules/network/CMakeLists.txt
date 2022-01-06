aux_source_directory(. ONVIF_NETWORK)

add_library(onvif_network SHARED)
target_include_directories(onvif_network PRIVATE ${PROJECT_SOURCE_DIR}/include/network)
set_target_properties(onvif_network PROPERTIES VERSION 0.0.2 SOVERSION 0 PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/network/network.h)
target_sources(onvif_network PRIVATE ${ONVIF_NETWORK})

install(TARGETS onvif_network
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib
		PUBLIC_HEADER DESTINATION onvif/include/network)