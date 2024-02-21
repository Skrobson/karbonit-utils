set(logger_src
	spdlogEngine/spdlogEngine.cpp
)

add_library(KitLogger
	STATIC
	${logger_src}
)

target_link_libraries(KitLogger
	PUBLIC
	spdlog::spdlog
)

target_include_directories(KitLogger
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include

)

install(TARGETS KitLogger
	LIBRARY DESTINATION lib
)

add_executable(logTest
	test.cpp)

target_link_libraries(logTest KitLogger)
target_include_directories(logTest
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
