ADD_SUBDIRECTORY(onvif)
ADD_SUBDIRECTORY(connection)
ADD_SUBDIRECTORY(management)
ADD_SUBDIRECTORY(network)
ADD_SUBDIRECTORY(memory)


AUX_SOURCE_DIRECTORY(. STUB)

ADD_LIBRARY(onvif SHARED)
SET_TARGET_PROPERTIES(onvif PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif PRIVATE ${STUB})
TARGET_LINK_LIBRARIES(onvif PRIVATE onvif_connection onvif_management onvif_network onvif_memory -Wl,--wrap,malloc -Wl,--wrap,free)

ADD_LIBRARY(onvif_static)
SET_TARGET_PROPERTIES(onvif_static PROPERTIES VERSION 0.0.2 SOVERSION 0)
SET_TARGET_PROPERTIES(onvif_static PROPERTIES OUTPUT_NAME "onvif")
TARGET_SOURCES(onvif_static PRIVATE ${STUB})
TARGET_LINK_LIBRARIES(onvif_static PRIVATE onvif_connection_static onvif_management_static onvif_network_static onvif_memory_static -Wl,--wrap,malloc -Wl,--wrap,free)

INSTALL(TARGETS onvif onvif_static
		EXPORT onvif_target
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)
INSTALL(DIRECTORY include/
		DESTINATION onvif/include)