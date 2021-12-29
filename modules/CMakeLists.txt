add_subdirectory(cJSON)
add_subdirectory(connection)
add_subdirectory(management)
add_subdirectory(memory)
add_subdirectory(network)
add_subdirectory(onvif)

install(DIRECTORY include/
		DESTINATION onvif/include)