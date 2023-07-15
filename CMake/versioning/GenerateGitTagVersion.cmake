find_package(Git REQUIRED)


set(HEADER_SRC ${CMAKE_CURRENT_LIST_DIR}/version.h.in)
set(CMAKE_SRC ${CMAKE_CURRENT_LIST_DIR}/VersionForPackage.cmake.in)
set(src_directory ${PROJECT_SOURCE_DIR})

function(generateVersionFromGit version_lib_name)
set(VERLIB_BIN_DIR ${CMAKE_BINARY_DIR}/CMake-utils/versioning)

set(HEADER_DST ${VERLIB_BIN_DIR}/include/${version_lib_name}.hpp)
set(CMAKE_DST ${VERLIB_BIN_DIR}/${version_lib_name}ForPackage.cmake)

if(GIT_EXECUTABLE)
  message(STATUS "Generating version lib ${version_lib_name} for ${src_directory} directory.")
  
  execute_process(
    COMMAND ${GIT_EXECUTABLE} branch --show-current
    WORKING_DIRECTORY ${src_directory}
    OUTPUT_VARIABLE GIT_BRANCH_VERSION
    RESULT_VARIABLE GIT_BRANCH_ERROR_CODE   
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  
  # Generate a git-describe version string from Git repository tags
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --long --dirty --match "v*"
    WORKING_DIRECTORY ${src_directory}
    OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
    RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  if(NOT GIT_DESCRIBE_ERROR_CODE)
    set(VERSION_BRANCH ${GIT_BRANCH_VERSION})

  string(REGEX REPLACE "^v.?([0-9]+)\\..*" "\\1" VERSION_MAJOR "${GIT_DESCRIBE_VERSION}")
  string(REGEX REPLACE "^v.?[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${GIT_DESCRIBE_VERSION}")
  string(REGEX REPLACE "^v.?[0-9]+\\.[0-9]+-([0-9]+).*" "\\1" VERSION_PATCH "${GIT_DESCRIBE_VERSION}")
  string(REGEX REPLACE "^v.?[0-9]+\\.[0-9]+-[0-9]+-(.*)" "\\1" VERSION_SHA1 "${GIT_DESCRIBE_VERSION}")
  
  set(VERSION_STRING "${GIT_BRANCH_VERSION}_${VERSION_MAJOR}.${VERSION_MINOR}-${VERSION_PATCH}.${VERSION_SHA1}")
  
  set(VER_LIB ${version_lib_name})

  endif()

endif()

# Final fallback: Just use a bogus version string that is semantically older
# than anything else and spit out a warning to the developer.
if(NOT DEFINED VERSION_STRING)
  set(VERSION_STRING v0.0.0-unknown)
  message(WARNING "Failed to determine VERSION_STRING from Git tags. Using default version \"${VERSION_STRING}\".")
else()
message(STATUS "Generate version ${VERSION_STRING}")
endif()

configure_file(${HEADER_SRC} ${HEADER_DST} @ONLY)
configure_file(${CMAKE_SRC} ${CMAKE_DST} @ONLY)

add_library(${version_lib_name} INTERFACE)
target_include_directories(${version_lib_name} INTERFACE ${VERLIB_BIN_DIR}/include)

include(${VERLIB_BIN_DIR}/${version_lib_name}ForPackage.cmake)

endfunction()