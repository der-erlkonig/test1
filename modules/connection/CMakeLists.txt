AUX_SOURCE_DIRECTORY(. ONVIF_CONNECTION)

ADD_LIBRARY(onvif_connection SHARED)
SET_TARGET_PROPERTIES(onvif_connection PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif_connection PRIVATE ${ONVIF_CONNECTION})
set_target_properties(onvif_connection PROPERTIES LINK_FLAGS "${LINK_FLAGS} -Wl,--wrap,malloc -Wl,--wrap,free")
TARGET_LINK_LIBRARIES(onvif_connection PRIVATE onvif_plugins onvif_custom onvif_memory)

INSTALL(TARGETS onvif_connection
		LIBRARY DESTINATION onvif/lib)