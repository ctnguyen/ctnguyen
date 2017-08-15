#################################################################
#  Date             14/08/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2017 CTN Software Ltd. All rights reserved    
#################################################################

cmake_minimum_required (VERSION 3.7)

# cmake path/to/source/folder/ -G"Visual Studio 12 2013 Win64"
# cmake path/to/source/folder/ -G"Eclipse CDT4 - Unix Makefiles"
# cmake path/to/source/folder/ -G"CodeBlocks – Unix Makefiles"

project(testBoost)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)
endif()

set(CMAKE_CXX_STANDARD 11)#Use C++11
cmake_policy(SET CMP0057 NEW)# USE IN_LIST functionality, example: if(${proj} IN_LIST PLUGIN_LIST)

if(NOT CMAKE_BUILD_TYPE AND NOT MSVC)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Add option [-DCMAKE_BUILD_TYPE=Debug] to build in debug mode" FORCE)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)#
enable_testing()

### Get the machine info
include(${CMAKE_SOURCE_DIR}/cmake/MachineInfoSetting.cmake)

## PRESETTING BUILD FOLDERS
include(${CMAKE_SOURCE_DIR}/cmake/buildsetting/SetBuildFolders.cmake)
CTNSetBuildFolders()

### Find boost
include(${CMAKE_SOURCE_DIR}/cmake/findpackage/CTNFindBoost.cmake)

### Test found package
include(${CMAKE_SOURCE_DIR}/cmake/InvestigateTargetProperties.cmake)
#echo_target(Boost::system)
#echo_target(Boost::date_time)
#echo_target(Boost::regex)
#echo_target(Boost::unit_test_framework)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(test)



##### Post config if exist
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)
endif()