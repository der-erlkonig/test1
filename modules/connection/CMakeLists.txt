AUX_SOURCE_DIRECTORY(. ONVIF_CONNECTION)

ADD_LIBRARY(onvif_connection SHARED)
SET_TARGET_PROPERTIES(onvif_connection PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif_connection PRIVATE ${ONVIF_CONNECTION})
TARGET_LINK_LIBRARIES(onvif_connection PRIVATE onvif_core)

ADD_LIBRARY(onvif_connection_static)
SET_TARGET_PROPERTIES(onvif_connection_static PROPERTIES VERSION 0.0.2 SOVERSION 0)
SET_TARGET_PROPERTIES(onvif_connection_static PROPERTIES OUTPUT_NAME "onvif_connection")
TARGET_SOURCES(onvif_connection_static PRIVATE ${ONVIF_CONNECTION})
TARGET_LINK_LIBRARIES(onvif_connection_static PRIVATE onvif_core_static)

INSTALL(TARGETS onvif_connection onvif_connection_static
		EXPORT onvif_connection_target
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)