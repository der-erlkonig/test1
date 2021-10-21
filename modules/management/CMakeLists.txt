AUX_SOURCE_DIRECTORY(. ONVIF_MANAGEMENT)

ADD_LIBRARY(onvif_management SHARED)
SET_TARGET_PROPERTIES(onvif_management PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif_management PRIVATE ${ONVIF_MANAGEMENT})
TARGET_LINK_LIBRARIES(onvif_management PRIVATE cjson)

ADD_LIBRARY(onvif_management_static)
SET_TARGET_PROPERTIES(onvif_management_static PROPERTIES VERSION 0.0.2 SOVERSION 0)
SET_TARGET_PROPERTIES(onvif_management_static PROPERTIES OUTPUT_NAME "onvif_management")
TARGET_SOURCES(onvif_management_static PRIVATE ${ONVIF_MANAGEMENT})
TARGET_LINK_LIBRARIES(onvif_management_static PRIVATE cjson)

INSTALL(TARGETS onvif_management onvif_management_static
		EXPORT onvif_management_target
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)