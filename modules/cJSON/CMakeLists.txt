aux_source_directory(. CJSON)

add_library(cjson SHARED)
set_target_properties(cjson PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_include_directories(cjson PRIVATE ${PROJECT_SOURCE_DIR}/include/cJSON)
target_sources(cjson PRIVATE ${CJSON})

add_library(cjson_static STATIC)
target_include_directories(cjson_static PRIVATE ${PROJECT_SOURCE_DIR}/include/cJSON)
target_sources(cjson_static PRIVATE ${CJSON})
set_target_properties(cjson_static PROPERTIES OUTPUT_NAME "cjson")

install(TARGETS cjson cjson_static
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)