#################################################
#                                               #
#   C++ PROGRAMMING                             #
#   MASTER LAURE ELIE 2013-2014                 #
#   Student Chi Thanh NGUYEN                    # 
#                                               #
#   chithanhnguyen.math@gmail.com               #
#################################################

#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 2.8)

project(m2m0_20132014) 

if(UNIX AND NOT APPLE)
    set(CMAKE_GENERATOR "Eclipse CDT4 - Unix Makefiles")
elseif(APPLE)

elseif(WIN32)
    set(CMAKE_GENERATOR "Visual Studio 10")
endif()
message("[M2MO Project] == Building with CMAKE_GENERATOR="${CMAKE_GENERATOR})



# include the project configuration 
if(EXISTS "${CMAKE_SOURCE_DIR}/user-config.cmake")
    include(${CMAKE_SOURCE_DIR}/user-config.cmake)
else()
    include(${CMAKE_SOURCE_DIR}/config.cmake)
endif()

include_directories(include)
add_subdirectory(src)
add_subdirectory(prog)
