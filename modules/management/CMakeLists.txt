aux_source_directory(. ONVIF_MANAGEMENT)
set(INC_ROOT ${PROJECT_SOURCE_DIR}/include/management)
set(INC ${INC_ROOT}/manage.h)

add_library(onvif_management SHARED)
set_target_properties(onvif_management PROPERTIES VERSION 0.0.2 SOVERSION 0 PUBLIC_HEADER "${INC}")
target_include_directories(onvif_management PRIVATE ${PROJECT_SOURCE_DIR}/include/management)
target_include_directories(onvif_management PRIVATE ${PROJECT_SOURCE_DIR}/include/connection)
target_include_directories(onvif_management PRIVATE ${PROJECT_SOURCE_DIR}/include/network)
target_include_directories(onvif_management PRIVATE ${PROJECT_SOURCE_DIR}/include/cJSON)
target_sources(onvif_management PRIVATE ${ONVIF_MANAGEMENT})
target_link_libraries(onvif_management PRIVATE cjson)

install(TARGETS onvif_management
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib
		PUBLIC_HEADER DESTINATION onvif/include/management)