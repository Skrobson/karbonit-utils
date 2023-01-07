find_package(Git REQUIRED)


set(HEADER_SRC ${CMAKE_CURRENT_LIST_DIR}/version.h.in)
set(CMAKE_SRC ${CMAKE_CURRENT_LIST_DIR}/VersionForPackage.cmake.in)

function(generateVersionFromGit version_lib_name src_directory)

set(HEADER_DST ${CMAKE_BINARY_DIR}/utils/CMake/versioning/include/${version_lib_name}.h)
set(CMAKE_DST ${CMAKE_BINARY_DIR}/utils/CMake/versioning/${version_lib_name}ForPackage.cmake)

if(GIT_EXECUTABLE)
  message(STATUS "GenerateVersion ${version_lib_name} for ${src_directory} directory.")
  # Generate a git-describe version string from Git repository tags
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --long --dirty --match "v*"
    WORKING_DIRECTORY ${src_directory}
    OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
    RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  if(NOT GIT_DESCRIBE_ERROR_CODE)
    set(VERSION_STRING ${GIT_DESCRIBE_VERSION})
   
  string(REGEX REPLACE "^v.?([0-9]+[0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION_STRING}")
  string(REGEX REPLACE "^v.?[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION_STRING}")
  string(REGEX REPLACE "^v.?[0-9]+\\.[0-9]+-([0-9]+).*" "\\1" VERSION_PATCH "${VERSION_STRING}")
  string(REGEX REPLACE "^v.?[0-9]+\\.[0-9]+-[0-9]+-(.*)" "\\1" VERSION_SHA1 "${VERSION_STRING}")
  set(VER_LIB ${version_lib_name})
  endif()
endif()

# Final fallback: Just use a bogus version string that is semantically older
# than anything else and spit out a warning to the developer.
if(NOT DEFINED VERSION_STRING)
  set(VERSION_STRING v0.0.0-unknown)
  message(WARNING "Failed to determine VERSION_STRING from Git tags. Using default version \"${VERSION_STRING}\".")
endif()

configure_file(${HEADER_SRC} ${HEADER_DST} @ONLY)
configure_file(${CMAKE_SRC} ${CMAKE_DST} @ONLY)

add_library(${version_lib_name} INTERFACE)
target_include_directories(${version_lib_name} INTERFACE ${CMAKE_BINARY_DIR}/utils/CMake/versioning/include)

include(${CMAKE_BINARY_DIR}/utils/CMake/versioning/${version_lib_name}ForPackage.cmake)

endfunction()