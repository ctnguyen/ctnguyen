#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

# cmake path/to/source/folder/ -G"Visual Studio 12 2013 Win64"
# cmake path/to/source/folder/ -G"Eclipse CDT4 - Unix Makefiles"
# cmake path/to/source/folder/ -G"CodeBlocks – Unix Makefiles"

add_definitions(-DBOOST_ALL_DYN_LINK) # Use boost dll versions, lib without lib prefix
find_package(Boost REQUIRED COMPONENTS iostreams filesystem system unit_test_framework)
message("                      include boost [${Boost_INCLUDE_DIR}]")
message("                          lib boost [${Boost_LIBRARIES}]")
include_directories(${Boost_INCLUDE_DIR})

add_executable(large_file_test large_file_test.cpp)
target_link_libraries(large_file_test ${Boost_LIBRARIES})

add_executable(mapped_file_test constants.hpp temp_file.hpp verification.hpp mapped_file_test.cpp)
target_link_libraries(mapped_file_test ${Boost_LIBRARIES})