find_library(SSL ssl REQUIRED)
find_library(CRYPTO crypto REQUIRED)
find_library(DL dl REQUIRED)
find_library(PTHREAD pthread REQUIRED)

aux_source_directory(. ONVIF_BASE)
add_library(onvif_base SHARED)
set_target_properties(onvif_base PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_sources(onvif_base PRIVATE ${ONVIF_BASE})
target_link_libraries(onvif_base PRIVATE ${SSL} ${CRYPTO} ${DL} ${PTHREAD} onvif_custom)

add_subdirectory(custom)
add_subdirectory(plugins)

install(TARGETS onvif_base
		LIBRARY DESTINATION onvif/lib)
install(FILES namespace.h soapH.h soapStub.h stdsoap2.h
		DESTINATION onvif/include)