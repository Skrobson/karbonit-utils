set(logger_src
	KitLogManager.cpp
)

add_library(KitLogger
	STATIC
	${logger_src}
)

target_link_libraries(KitLogger
	PUBLIC
	spdlog::spdlog
	Singleton
)

target_include_directories(KitLogger
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	Singleton
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
	Singleton
)
