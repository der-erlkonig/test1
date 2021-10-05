#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cjson_utils" for configuration "Release"
set_property(TARGET cjson_utils APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cjson_utils PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "cjson"
  IMPORTED_LOCATION_RELEASE "/home/changchun/json-c/lib/libcjson_utils.so.1.7.15"
  IMPORTED_SONAME_RELEASE "libcjson_utils.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS cjson_utils )
list(APPEND _IMPORT_CHECK_FILES_FOR_cjson_utils "/home/changchun/json-c/lib/libcjson_utils.so.1.7.15" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
