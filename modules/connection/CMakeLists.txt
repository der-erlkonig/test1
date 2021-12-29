aux_source_directory(. ONVIF_CONNECTION)

add_library(onvif_connection SHARED)
set_target_properties(onvif_connection PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_sources(onvif_connection PRIVATE ${ONVIF_CONNECTION})
target_link_libraries(onvif_connection PRIVATE onvif_plugins onvif_custom)

install(TARGETS onvif_connection
		LIBRARY DESTINATION onvif/lib)