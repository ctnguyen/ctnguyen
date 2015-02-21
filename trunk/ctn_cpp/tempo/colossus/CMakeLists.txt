#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 2.8)

# cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 /path/to/source/code

project(colossus) 

add_library(ctn_lib DataStream.h DataStream.cpp)

add_executable(ctn_prog "main.cpp")
target_link_libraries(ctn_prog ctn_lib)

# For tests
enable_testing()
add_subdirectory(test)


