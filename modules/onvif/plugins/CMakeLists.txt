SET(ONVIF_PLUGINS wsseapi.c wsaapi.c threads.c smdevp.c mecevp.c)

ADD_LIBRARY(onvif_plugins SHARED)
SET_TARGET_PROPERTIES(onvif_plugins PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif_plugins PRIVATE ${ONVIF_PLUGINS})
TARGET_LINK_LIBRARIES(onvif_plugins onvif_base)

ADD_LIBRARY(onvif_plugins_static)
SET_TARGET_PROPERTIES(onvif_plugins_static PROPERTIES VERSION 0.0.2 SOVERSION 0)
SET_TARGET_PROPERTIES(onvif_plugins_static PROPERTIES OUTPUT_NAME "onvif_plugins")
TARGET_SOURCES(onvif_plugins_static PRIVATE ${ONVIF_PLUGINS})
TARGET_LINK_LIBRARIES(onvif_plugins_static onvif_base_static)

INSTALL(TARGETS onvif_plugins onvif_plugins_static
		EXPORT onvif_pluins_targets
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)

INSTALL(FILES wsseapi.h wsaapi.h threads.h smdevp.h mecevp.h DESTINATION onvif/plugins/include)