aux_source_directory(. ONVIF_MANAGEMENT)

add_library(onvif_management SHARED)
set_target_properties(onvif_management PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_sources(onvif_management PRIVATE ${ONVIF_MANAGEMENT})
target_link_libraries(onvif_management PRIVATE cjson)

install(TARGETS onvif_management
		LIBRARY DESTINATION onvif/lib)