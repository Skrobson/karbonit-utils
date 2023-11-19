add_library(BoostSignalsProxy INTERFACE

)

target_link_libraries(BoostSignalsProxy INTERFACE
    Boost::boost
)

target_include_directories(BoostSignalsProxy INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
    #${Boost_INCLUDE_DIRS}
)
