aux_source_directory(. ONVIF_NETWORK)

add_library(onvif_network SHARED)
set_target_properties(onvif_network PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_sources(onvif_network PRIVATE ${ONVIF_NETWORK})

install(TARGETS onvif_network
		LIBRARY DESTINATION onvif/lib)