aux_source_directory(. ONVIF_CONNECTION)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/include/connection)
set(INC ${INC_ROOT}/device.h ${INC_ROOT}/discovery.h ${INC_ROOT}/media.h ${INC_ROOT}/ptz.h)

add_library(onvif_connection SHARED)
set_target_properties(onvif_connection PROPERTIES VERSION 0.0.2 SOVERSION 0 PUBLIC_HEADER "${INC}")
target_include_directories(onvif_connection PRIVATE ${PROJECT_SOURCE_DIR}/include/connection)
target_include_directories(onvif_connection PRIVATE ${PROJECT_SOURCE_DIR}/include/onvif)
target_sources(onvif_connection PRIVATE ${ONVIF_CONNECTION})
target_link_libraries(onvif_connection PRIVATE onvif_core)

add_library(onvif_connection_static STATIC)
target_include_directories(onvif_connection_static PRIVATE ${PROJECT_SOURCE_DIR}/include/connection)
target_include_directories(onvif_connection_static PRIVATE ${PROJECT_SOURCE_DIR}/include/onvif)
target_sources(onvif_connection_static PRIVATE ${ONVIF_CONNECTION})
set_target_properties(onvif_connection_static PROPERTIES OUTPUT_NAME "onvif_connection")

install(TARGETS onvif_connection onvif_connection_static
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib
		PUBLIC_HEADER DESTINATION onvif/include/connection)