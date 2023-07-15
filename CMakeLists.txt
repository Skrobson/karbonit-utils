cmake_minimum_required (VERSION 3.18)

project("karbonit-utils")

#set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(Boost 1.71 REQUIRED COMPONENTS system log log_setup thread program_options filesystem iostreams)

#Boost static link
#set(Boost_USE_STATIC_LIBS ON)
#

#Boost dynamic link
if (WIN32)
    # disable autolinking in boost
    add_definitions( -DBOOST_ALL_NO_LIB )

    # force all boost libraries to dynamic link (we already disabled
    # autolinking, so I don't know why we need this, but we do!)
    add_definitions( -DBOOST_ALL_DYN_LINK )

endif()
set (Boost_USE_STATIC_LIBS OFF CACHE BOOL "use static libraries from Boost")
#

add_subdirectory(src)