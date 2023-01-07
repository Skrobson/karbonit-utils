set(HEADER_SRC ${CMAKE_CURRENT_LIST_DIR}/version.h.in)
set(HEADER_DST ${CMAKE_BINARY_DIR}/utils/CMake/versioning/version.h)

set(CMAKE_SRC ${CMAKE_CURRENT_LIST_DIR}/VersionForPackage.cmake.in)
set(CMAKE_DST ${CMAKE_BINARY_DIR}/utils/CMake/versioning/VersionForPackage.cmake)

function(generateVersionFromGit)
if(GIT_EXECUTABLE)
  message(STATUS "GenerateVersionHeader for: ${DIRECTORY}")
  # Generate a git-describe version string from Git repository tags
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --long --dirty --match "v*"
    WORKING_DIRECTORY ${DIRECTORY}
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
endfunction()