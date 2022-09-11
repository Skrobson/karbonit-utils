set(logger_src 

)

add_library(Logger 
	STATIC	
	${logger_src}
)

target_link_libraries(Logger
	PUBLIC
	Singleton
)

target_include_directories(Logger
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	Singleton
)

install(TARGETS Logger 
	LIBRARY DESTINATION lib 
)
