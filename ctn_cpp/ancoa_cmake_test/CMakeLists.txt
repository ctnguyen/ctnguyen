#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

# For Visual Studio 12 2013, x64 use generator 
# -G"Visual Studio 12 2013 Win64"
# Be sure that every libraries (Boost, Qt) are built in x64 version.

project(ancoa_cmake_test) 

# Set modules directories
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

option(BUILD_SHARED_LIBS "Build All lib in shared" ON)

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(Proj1)
add_subdirectory(Proj2)
add_subdirectory(ProjA)
add_subdirectory(ProjB)

add_subdirectory(Prog1A)
add_subdirectory(Prog2B)

## Find Qt, if found, add this projects
add_subdirectory(ProjQtTest)


# if found boost test framework, go into the test folder
find_package(Boost COMPONENTS)
## Attention to the structure of the boost library that has 
## ${BOOST_ROOT}/boost         all include here
## ${BOOST_ROOT}/lib           all lib and dll here
if(Boost_FOUND)
    include(CTest)
    include_directories(${Boost_INCLUDE_DIRS})
    add_subdirectory(Test)
endif()