cmake_minimum_required(VERSION 3.1)
project(onvif_client VERSION 0.0.2)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wmissing-prototypes -DWITH_OPENSSL -DWITH_DOM")
if(SOAP_TIMEOUT)
	add_definitions("-DSOAP_TIMEOUT=${SOAP_TIMEOUT}")
endif()
execute_process(COMMAND sh manual.sh)

add_subdirectory(modules)

install(FILES README.txt version.txt manual.pdf DESTINATION onvif/share)
install(FILES include/onvif.h DESTINATION onvif/include)