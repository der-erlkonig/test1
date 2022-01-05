set(ONVIF_CUSTOM struct_timeval.c)
add_library(onvif_custom SHARED)
set_target_properties(onvif_custom PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_sources(onvif_custom PRIVATE ${ONVIF_CUSTOM})

install(TARGETS onvif_custom
		LIBRARY DESTINATION onvif/lib)