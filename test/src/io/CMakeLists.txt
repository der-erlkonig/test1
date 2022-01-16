add_executable(io.properties.t1 test_properties1.c)
target_include_directories(io.properties.t1 PRIVATE ${PROJECT_SOURCE_DIR}/include/io)
target_include_directories(io.properties.t1 PRIVATE ${PROJECT_SOURCE_DIR}/test/include)
target_link_libraries(io.properties.t1 PRIVATE config_io)

add_test(NAME io/properties/t1 COMMAND io.properties.t1)