project(BoostExtensions)

add_subdirectory(SignalsProxy)


add_library(BoostExtensions INTERFACE)

# Link the master library with the other libraries
target_link_libraries(BoostExtensions INTERFACE
    BoostSignalsProxy
)

target_include_directories(BoostExtensions INTERFACE 
    BoostSignalsProxy
)