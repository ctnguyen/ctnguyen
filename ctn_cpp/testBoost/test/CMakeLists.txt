#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

# cmake path/to/source/folder/ -G"Visual Studio 12 2013 Win64"
# cmake path/to/source/folder/ -G"Eclipse CDT4 - Unix Makefiles"
# cmake path/to/source/folder/ -G"CodeBlocks – Unix Makefiles"

find_package(Boost REQUIRED COMPONENTS serialization)
message("                      include boost [${Boost_INCLUDE_DIR}]")
message("                          lib boost [${Boost_LIBRARIES}]")
include_directories(${Boost_INCLUDE_DIR})

add_executable(test_Boost_Serialization test_Boost_Serialization.cpp)
target_link_libraries(test_Boost_Serialization ${Boost_LIBRARIES})
