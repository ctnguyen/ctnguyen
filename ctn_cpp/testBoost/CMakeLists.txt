#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

project(testBoost) 

# cmake path/to/source/folder/ -G"Visual Studio 12 2013 Win64"
# cmake path/to/source/folder/ -G"Eclipse CDT4 - Unix Makefiles"
# cmake path/to/source/folder/ -G"CodeBlocks – Unix Makefiles"

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(test)
