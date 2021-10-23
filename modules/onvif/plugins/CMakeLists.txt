SET(ONVIF_PLUGINS wsseapi.c wsaapi.c threads.c smdevp.c mecevp.c)

ADD_LIBRARY(onvif_plugins SHARED)
SET_TARGET_PROPERTIES(onvif_plugins PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif_plugins PRIVATE ${ONVIF_PLUGINS})
set_target_properties(onvif_plugins PROPERTIES LINK_FLAGS "${LINK_FLAGS} -Wl,--wrap,malloc -Wl,--wrap,free")
TARGET_LINK_LIBRARIES(onvif_plugins PRIVATE onvif_base onvif_memory)

INSTALL(TARGETS onvif_plugins
		LIBRARY DESTINATION onvif/lib)

INSTALL(FILES wsseapi.h wsaapi.h threads.h smdevp.h mecevp.h DESTINATION onvif/include/plugins)
