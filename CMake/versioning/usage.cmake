###################################
#  Generate Version from Git tag  #
#  Tags should begin with "v"     #
###################################
find_package(Git)

set(SRC ${CMAKE_SOURCE_DIR}/version.h.in)
set(DST ${CMAKE_BINARY_DIR}/version.h)
set(CMAKE_SRC ${CMAKE_SOURCE_DIR}/VersionForPackage.cmake.in)
set(CMAKE_DST ${CMAKE_BINARY_DIR}/VersionForPackage.cmake)
set(GIT_EXECUTABLE ${GIT_EXECUTABLE})

set(VERSION_STRING "")
add_custom_target(version ALL
  ${CMAKE_COMMAND} -D SRC=${CMAKE_SOURCE_DIR}/version.h.in
                   -D DST=${CMAKE_BINARY_DIR}/version.h                   
                   -D CMAKE_SRC=${CMAKE_SOURCE_DIR}/VersionForPackage.cmake.in
                   -D CMAKE_DST=${CMAKE_BINARY_DIR}/VersionForPackage.cmake
                   -D GIT_EXECUTABLE=${GIT_EXECUTABLE}
                   -P ${CMAKE_SOURCE_DIR}/GenerateVersionHeader.cmake
                   VERBATIM
)


include(${CMAKE_SOURCE_DIR}/GenerateVersionHeader.cmake)
generateVersionFromGit() 
include("${CMAKE_BINARY_DIR}/VersionForPackage.cmake")


message("${PROJECT_NAME} Version ${VERSION_MAJOR}.
${VERSION_MINOR}.
${VERSION_PATCH}")
message("${PROJECT_NAME} Version ${VERSION_STRING}")


set(CPACK_PACKAGE_NAME "example")
set(CPACK_PACKAGE_VENDOR "KarbonIT")

set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})

set(CPACK_PACKAGE_FILE_NAME "example-v${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${VERSION_SHA1}")