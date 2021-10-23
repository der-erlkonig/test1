AUX_SOURCE_DIRECTORY(. ONVIF_NETWORK)

ADD_LIBRARY(onvif_network SHARED)
SET_TARGET_PROPERTIES(onvif_network PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif_network PRIVATE ${ONVIF_NETWORK})
set_target_properties(onvif_network PROPERTIES LINK_FLAGS "${LINK_FLAGS} -Wl,--wrap,malloc -Wl,--wrap,free")
target_link_libraries(onvif_network PRIVATE onvif_memory)

INSTALL(TARGETS onvif_network
		LIBRARY DESTINATION onvif/lib)