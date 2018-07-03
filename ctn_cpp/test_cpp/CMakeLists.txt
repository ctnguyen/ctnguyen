############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################

set(SOURCE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)
    message(STATUS "Preconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake] has been included")
endif()

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/ImportConfig.cmake)## ADD IMPORT CONFIG BUILD IF EXIST 
    include(${CMAKE_CURRENT_BINARY_DIR}/ImportConfig.cmake)
    message(STATUS "Build configuration has been imported [${CMAKE_CURRENT_BINARY_DIR}/ImportConfig.cmake]")
endif()

set(boost_MINIMUM_REQUIRED 1.66)

# Minimum requirements :
#   cmake 3.10.2
#   C++ 14
#   boost 1.66
#   Crypto++ 5.6.5
#   VS2015 x64 Native Tools Command Prompt
#
# Be sure that every libraries (Boost) are built in x64 version.
# Make sure to have the BOOST_ROOT defined in environment variables
#
# For Visual Studio, add MSBuild to the path
#   For community   version, MSBuild is in MSBuild.exe
#   For profesional version, MSBuild is in "C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe"
#
# Build single command
#
# cmake -G"Visual Studio 15 2017 Win64" ..\ctnguyen\ctn_cpp\test_cpp -DDEV_BUILD=ON && MSBuild.exe CTN.sln /P:Configuration=Debug /maxcpucount:8 && ctest -C Debug && MSBuild.exe CTN.sln /P:Configuration=Release /maxcpucount:8 && ctest -C Release
# cmake --build . --target install #--config Debug
#
# cmake ../ctnguyen/ctn_cpp/test_cpp -DDEV_BUILD=ON -DCMAKE_BUILD_TYPE=Debug && make -j8 && ctest
#
# cpack -C Release -G NSIS --config CPackConfig.cmake
#
# Production build
#
cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/INSTALLATION" CACHE PATH "Cmake prefix" FORCE)# Force the install directory 

project(CTN)
# -DDEV_BUILD=ON will build all tests, examples

set(CTN_EXPORT_VARIABLES "" CACHE INTERNAL "List of important variable to export" FORCE)# First setting of the list and initialize by DEV_BUILD

if(NOT MSVC AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Add option [-DCMAKE_BUILD_TYPE=Debug] to build in debug mode" FORCE)
endif()

# Set modules directories
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/MachineInfoSetting.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SystemSetting.cmake)

## PRESETTING BUILD FOLDERS
include(${SOURCE_ROOT_DIR}/cmake/buildsetting/BuildSetting.cmake)
SetCompilationOptions()
SetBuildFolders() ## Set folder to put all shared lib and executable together
SetBuildVersion()
SetBuildVariables()

## Setting to make executable and shared libraries relocatable
include(${SOURCE_ROOT_DIR}/cmake/installsetting/InstallSetting.cmake)
setRelocatability()

## Add cortire helper for accelerating build time
if(BUILD_WITH_COTIRE)
    include(${SOURCE_ROOT_DIR}/cmake/buildsetting/cotire.cmake)
    set(COTIRE_TARGETS_FOLDER "_cotire")
endif()
## Add build with cotire functionalities to reduce compile time
#if(BUILD_WITH_COTIRE)
#    cotire(myTarget)
#    #set_target_properties(myTarget PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
#endif()

###################################################
##########    FIND EXTERNAL LIBRARIES     #########
include(${SOURCE_ROOT_DIR}/cmake/InvestigateTargetProperties.cmake)

### Linking with Boost
#set(Project_Required_BOOST_COMPONENTS system) ## It just to test FindBoostHelper for a single component system
include(${SOURCE_ROOT_DIR}/cmake/findpackage/FindBoostHelper.cmake)
#echo_target(Boost::system)
include(${SOURCE_ROOT_DIR}/cmake/findpackage/FindCryptoPPHelper.cmake)
include(${SOURCE_ROOT_DIR}/cmake/findpackage/FindOpenSSLHelper.cmake)
#print_openssl_info()

# Ensure RapidJSON is installed in the system
if(NOT DEFINED ENV{RAPIDJSON_ROOT})
    message(FATAL_ERROR "Missing RapidJSON library. Download it from http://rapidjson.org and define the environment variable RAPIDJSON_ROOT to this directory")
else()
    message(STATUS "  Found RapidJSON at [$ENV{RAPIDJSON_ROOT}]")
    message(STATUS "    Usage :")
    message(STATUS "    target_include_directories(mytarget PUBLIC \${RAPIDJSON_ROOT}/include)")
    set(RAPIDJSON_ROOT $ENV{RAPIDJSON_ROOT})
endif()

## Find Telegram Bot API library. Need to set TGBOT_ROOT environment variable
## Make sure to use the file TgBot.CMakeLists.txt in $ROOT/cmake/findpackage to build and install TgBot
include(${SOURCE_ROOT_DIR}/cmake/findpackage/FindTgBotHelper.cmake)

## Find TBB package in CONFIG mode. Need to set env variable TBB_DIR pointing to the root of the installed TBB
## Found components are TBB::  tbb, tbbmalloc, tbbproxy, tbbmalloc_proxy
include(${SOURCE_ROOT_DIR}/cmake/findpackage/FindTBBHelper.cmake)
#print_tbb_info()


######## BUILD c++ PROGRAMS #######
################################################################################################
################################################################################################

enable_testing()
add_subdirectory(${SOURCE_ROOT_DIR}/test)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)
    message(STATUS "Postconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake] has been included")
endif()

print_system_info()
print_buildsetting_info()

# Print and export build variables so one can reproduce exactly the same build
print_export_variables()
copyExportBuildVariable()
