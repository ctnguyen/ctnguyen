link_directories(${CMAKE_BINARY_DIR}/modules)

add_executable(say_hello say_hello.cpp)

target_link_libraries(say_hello
	hello_english
	hello_french
	hello_vietnamese
)
