#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

# cmake path/to/source/folder/ -G"Visual Studio 12 2013 Win64"
# cmake path/to/source/folder/ -G"Eclipse CDT4 - Unix Makefiles"
# cmake path/to/source/folder/ -G"CodeBlocks – Unix Makefiles"

add_definitions(-DBOOST_ALL_DYN_LINK) # Use boost dll versions, lib without lib prefix
find_package(Boost REQUIRED COMPONENTS serialization iostreams)
message("                      include boost [${Boost_INCLUDE_DIR}]")
message("                          lib boost [${Boost_LIBRARIES}]")
include_directories(${Boost_INCLUDE_DIR})

add_executable(test_Boost_Serialization test_Boost_Serialization.cpp)
target_link_libraries(test_Boost_Serialization ${Boost_LIBRARIES})
