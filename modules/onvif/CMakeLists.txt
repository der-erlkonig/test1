find_library(SSL ssl REQUIRED)
find_library(CRYPTO crypto REQUIRED)
find_library(DL dl REQUIRED)
find_library(PTHREAD pthread REQUIRED)

aux_source_directory(. ONVIF_CORE)
add_library(onvif_core SHARED)
set_target_properties(onvif_core PROPERTIES VERSION 0.0.2 SOVERSION 0)
target_include_directories(onvif_core PRIVATE ${PROJECT_SOURCE_DIR}/include/onvif)
target_sources(onvif_core PRIVATE ${ONVIF_CORE})
target_link_libraries(onvif_core PRIVATE ${SSL} ${CRYPTO} ${DL} ${PTHREAD})

install(TARGETS onvif_core
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)