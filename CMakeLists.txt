cmake_minimum_required (VERSION 3.18)

project("karbonit-utils")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#CMake modules

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/modules")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")


find_package(spdlog REQUIRED)
find_package(Boost 1.83 COMPONENTS system filesystem iostreams serialization thread REQUIRED)
find_package(GTest)

add_subdirectory(3rdParty)
add_subdirectory(src)
