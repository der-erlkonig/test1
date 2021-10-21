SET(ONVIF_CUSTOM struct_timeval.c)
ADD_LIBRARY(onvif_custom SHARED)
SET_TARGET_PROPERTIES(onvif_custom PROPERTIES VERSION 0.0.2 SOVERSION 0)
TARGET_SOURCES(onvif_custom PRIVATE ${ONVIF_CUSTOM})

ADD_LIBRARY(onvif_custom_static)
SET_TARGET_PROPERTIES(onvif_custom_static PROPERTIES VERSION 0.0.2 SOVERSION 0)
SET_TARGET_PROPERTIES(onvif_custom_static PROPERTIES OUTPUT_NAME "onvif_custom")
TARGET_SOURCES(onvif_custom_static PRIVATE ${ONVIF_CUSTOM})

INSTALL(TARGETS onvif_custom onvif_custom_static
		EXPORT onvif_custom_target
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)
INSTALL(FILES struct_timeval.h
		DESTINATION onvif/include/custom)