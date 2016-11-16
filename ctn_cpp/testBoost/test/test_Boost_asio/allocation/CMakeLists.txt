#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

# cmake path/to/source/folder/ -G"Visual Studio 12 2013 Win64"
# cmake path/to/source/folder/ -G"Eclipse CDT4 - Unix Makefiles"
# cmake path/to/source/folder/ -G"CodeBlocks – Unix Makefiles"

add_definitions(-DBOOST_ALL_DYN_LINK) # Use boost dll versions, lib without lib prefix
find_package(Boost REQUIRED COMPONENTS system date_time regex)
message("                       Boost_INCLUDE_DIR [${Boost_INCLUDE_DIR}]")
message("                      Boost_INCLUDE_DIRS [${Boost_INCLUDE_DIRS}]")
message("                         Boost_LIBRARIES [${Boost_LIBRARIES}]")
message("       Boost_UNIT_TEST_FRAMEWORK_LIBRARY [${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}]")
include_directories(${Boost_INCLUDE_DIRS})

add_executable(allocation allocation.cpp)
target_link_libraries(allocation ${Boost_LIBRARIES})
set_property(TARGET allocation PROPERTY FOLDER "test/allocation")