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

set(M2MO_HEAD_MESSAGE " [M2MO_Project]  =======  ") 


# include the project configuration file
if(EXISTS "${CMAKE_SOURCE_DIR}/user-config.cmake")
    include(${CMAKE_SOURCE_DIR}/user-config.cmake)
else()
    include(${CMAKE_SOURCE_DIR}/config.cmake)
endif()

# Setting the "normal" cmake generator, in case of special generator, modify user-config.cmake
if(NOT M2MO_USER_DEFINE_GENERATOR)
    if(UNIX AND NOT APPLE)
        set(CMAKE_GENERATOR "Eclipse CDT4 - Unix Makefiles")
    elseif(APPLE)
        set(CMAKE_GENERATOR "Xcode")
    elseif(WIN32)
        set(CMAKE_GENERATOR "Visual Studio 10")
    endif()
endif()
message("${M2MO_HEAD_MESSAGE}Building with CMAKE_GENERATOR='${CMAKE_GENERATOR}'")



include_directories(include)
add_subdirectory(src)
add_subdirectory(prog)

if(M2MO_BUILD_TEST)
    add_definitions(-DM2MO_BUILD_TEST)
    add_subdirectory(test)
endif()
