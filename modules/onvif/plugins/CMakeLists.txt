set(ONVIF_PLUGINS wsseapi.c wsaapi.c threads.c smdevp.c mecevp.c)

add_library(onvif_plugins SHARED)
set_target_properties(onvif_plugins PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_sources(onvif_plugins PRIVATE ${ONVIF_PLUGINS})
target_link_libraries(onvif_plugins PRIVATE onvif_base)

install(TARGETS onvif_plugins
		LIBRARY DESTINATION onvif/lib)
install(FILES wsseapi.h wsaapi.h threads.h smdevp.h mecevp.h DESTINATION onvif/include/plugins)