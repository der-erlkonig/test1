aux_source_directory(. ONVIF_CONNECTION)
file(GLOB INC ${PROJECT_SOURCE_DIR}/include/connection/*)

add_library(onvif_connection SHARED)
set_target_properties(onvif_connection PROPERTIES VERSION 0.0.2 SOVERSION 0 PUBLIC_HEADER "${INC}")
target_include_directories(onvif_connection PRIVATE ${PROJECT_SOURCE_DIR}/include/connection)
target_sources(onvif_connection PRIVATE ${ONVIF_CONNECTION})
target_link_libraries(onvif_connection PRIVATE onvif_plugins)

install(TARGETS onvif_connection
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib
		PUBLIC_HEADER DESTINATION onvif/include/connection)