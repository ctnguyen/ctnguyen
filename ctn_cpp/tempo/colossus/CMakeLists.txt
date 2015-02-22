#CMAKE INITIALIZATION
cmake_minimum_required(VERSION 3.0)

project(colossus) 

add_library(ctn_lib 
			DataStream.h
			helper.h
			Median.h
			Selection.h
			DataStream.cpp
			Median.cpp
			Selection.cpp)

add_executable(ctn_prog "main.cpp")
target_link_libraries(ctn_prog ctn_lib)

# For tests
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
enable_testing()
add_subdirectory(test)


