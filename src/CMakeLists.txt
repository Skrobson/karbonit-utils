find_package(Boost 1.71 REQUIRED COMPONENTS system thread program_options filesystem iostreams)

add_subdirectory(singleton)
add_subdirectory(logger)
add_subdirectory(misc)