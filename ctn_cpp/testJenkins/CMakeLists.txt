############################################################### #
#  Date             10/02/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#################################################################

# Be sure that every libraries (Boost, Qt) are built in x64 version.
# Make sure to have the QT_ROOT and BOOST_ROOT defined and point to the root library

cmake_minimum_required(VERSION 3.2)

#add_definitions(/wd4251 /wd4244 -D_SCL_SECURE_NO_WARNINGS)
#

# For Visual Studio 12 2013, x64 use generator 
# cmake -G"Visual Studio 12 2013 Win64" C:\path\to\this\folder
# "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" testJenkins.sln /P:Configuration=Release /maxcpucount:8
# "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" INSTALL.vcxproj /P:Configuration=Release
# "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" testJenkins.sln /P:Configuration=Debug /maxcpucount:8
# "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" INSTALL.vcxproj /P:Configuration=Debug
#
# Or single command
# cmake -G"Visual Studio 12 2013 Win64" C:\path\to\this\folder && "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" testJenkins.sln /P:Configuration=Debug /maxcpucount:8 /v:q && "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" testJenkins.sln /P:Configuration=Release /maxcpucount:8 /v:q
# cmake -G"Visual Studio 12 2013 Win64" C:\path\to\this\folder && "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" testJenkins.sln /P:Configuration=Debug /maxcpucount:8 /v:diag && "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" testJenkins.sln /P:Configuration=Release /maxcpucount:8 /v:diag
# cmake -G"Visual Studio 12 2013 Win64" C:\path\to\this\folder && "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" testJenkins.sln /P:Configuration=Debug /maxcpucount:8 && "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" testJenkins.sln /P:Configuration=Release /maxcpucount:8
#
project(testJenkins)

set(CMAKE_CXX_STANDARD 11)#Use C++11
cmake_policy(SET CMP0057 NEW)# USE IN_LIST functionality, example: if(${proj} IN_LIST PLUGIN_LIST)

if(NOT CMAKE_BUILD_TYPE AND NOT MSVC)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Add option [-DCMAKE_BUILD_TYPE=Debug] to build in debug mode" FORCE)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)## Could be MSVC only
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "_CMakePredefinedTarget" )

# Set modules directories
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(${CMAKE_SOURCE_DIR}/cmake/MyFindBoost.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/MyFindQt5.cmake)
# TODO add a test that take long time to execute (2 mins) to test jenkins build queue
#
