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

add_library(onvif_core_static STATIC)
target_include_directories(onvif_core_static PRIVATE ${PROJECT_SOURCE_DIR}/include/onvif)
target_sources(onvif_core_static PRIVATE ${ONVIF_CORE})
set_target_properties(onvif_core_static PROPERTIES OUTPUT_NAME "onvif_core")

install(TARGETS onvif_core onvif_core_static
		LIBRARY DESTINATION onvif/lib
		ARCHIVE DESTINATION onvif/lib)