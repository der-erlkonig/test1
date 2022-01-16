cmake_minimum_required(VERSION 3.1)
project(onvif_client VERSION 0.0.2)

add_definitions("-DWITH_OPENSSL -DWITH_DOM")
set(CMAKE_BUILD_TYPE "Release")
if(WITH_DEBUG)
	add_compile_options("-g -ggdb")
endif()

if(SOAP_TIMEOUT)
	add_definitions("-DSOAP_TIMEOUT=${SOAP_TIMEOUT}")
endif()

add_subdirectory(modules)

install(FILES README.txt version.txt DESTINATION onvif/share)
install(FILES include/onvif.h DESTINATION onvif/include)

enable_testing()
add_subdirectory(test)