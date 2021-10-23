aux_source_directory(. CJSON)
add_library(cjson SHARED)
set_target_properties(cjson PROPERTIES VERSION 0.0.2t SOVERSION 0t)
set_target_properties(cjson PROPERTIES LINK_FLAGS "${LINK_FLAGS} -Wl,--wrap,malloc -Wl,--wrap,free")
target_sources(cjson PRIVATE ${CJSON})
target_link_libraries(cjson PRIVATE onvif_memory)

install(TARGETS cjson
		LIBRARY DESTINATION onvif/lib)
install(FILES cJSON.h
		DESTINATION onvif/include/cJSON)
