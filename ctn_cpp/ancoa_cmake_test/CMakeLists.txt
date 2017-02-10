#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

# For Visual Studio 12 2013, x64 use generator 
# -G"Visual Studio 12 2013 Win64"
# Be sure that every libraries (Boost, Qt) are built in x64 version.
# Make sure to have the QT_ROOT and BOOST_ROOT defined and point to the root library
project(ancoa_cmake_test) 

# Set modules directories
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/InvestigateTargetProperties.cmake)

option(BUILD_SHARED_LIBS "Build All lib in shared" ON)

# Set Automoc for Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_SOURCE_DIR})
#add_subdirectory(Proj1)
#add_subdirectory(Proj2)
#add_subdirectory(ProjA)
#add_subdirectory(ProjB)

#add_subdirectory(Prog1A)
#add_subdirectory(Prog2B)

## Find Qt, if found, add this projects
##list(APPEND CMAKE_MODULE_PATH "C:/development/frameworks/qt/5.3.1/lib/cmake")
#add_subdirectory(ProjQtTest)
add_subdirectory(ProgQt)

#echo_target(ProgQt)#TARGET information from sub dir can be populated to root

# if found boost test framework, go into the test folder
#find_package(Boost COMPONENTS)
## Attention to the structure of the boost library that has 
## ${BOOST_ROOT}/boost         all include here
## ${BOOST_ROOT}/lib           all lib and dll here
if(Boost_FOUND)
    include(CTest)
    include_directories(${Boost_INCLUDE_DIRS})
    add_subdirectory(Test)
endif()