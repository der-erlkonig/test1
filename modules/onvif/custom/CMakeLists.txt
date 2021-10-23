SET(ONVIF_CUSTOM struct_timeval.c)
ADD_LIBRARY(onvif_custom SHARED)
SET_TARGET_PROPERTIES(onvif_custom PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif_custom PRIVATE ${ONVIF_CUSTOM})
set_target_properties(onvif_custom PROPERTIES LINK_FLAGS "${LINK_FLAGS} -Wl,--wrap,malloc -Wl,--wrap,free")
target_link_libraries(onvif_custom PRIVATE onvif_memory)

INSTALL(TARGETS onvif_custom
		LIBRARY DESTINATION onvif/lib)
INSTALL(FILES struct_timeval.h
		DESTINATION onvif/include/custom)