cmake_minimum_required (VERSION 3.18)

project("karbonit-utils")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(spdlog REQUIRED)
find_package(Boost 1.74.0 REQUIRED COMPONENTS system filesystem iostreams serialization thread)

add_subdirectory(3rdParty)
add_subdirectory(src)