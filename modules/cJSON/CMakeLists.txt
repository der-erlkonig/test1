aux_source_directory(. CJSON)
add_library(cjson SHARED)
set_target_properties(cjson PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_sources(cjson PRIVATE ${CJSON})

install(TARGETS cjson
		LIBRARY DESTINATION onvif/lib)