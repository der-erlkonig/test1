AUX_SOURCE_DIRECTORY(. ONVIF_MANAGEMENT)

ADD_LIBRARY(onvif_management SHARED)
SET_TARGET_PROPERTIES(onvif_management PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif_management PRIVATE ${ONVIF_MANAGEMENT})
set_target_properties(onvif_management PROPERTIES LINK_FLAGS "${LINK_FLAGS} -Wl,--wrap,malloc -Wl,--wrap,free")
TARGET_LINK_LIBRARIES(onvif_management PRIVATE cjson onvif_memory)

INSTALL(TARGETS onvif_management
		LIBRARY DESTINATION onvif/lib)