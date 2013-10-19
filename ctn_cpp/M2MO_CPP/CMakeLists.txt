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
    include(${CMAKE_SOURCE_DIR}/default-config.cmake)
endif()

# Setting the "normal" cmake generator, in case of special generator, modify user-config.cmake
if(NOT M2MO_USER_DEFINE_GENERATOR)
    if(UNIX AND NOT APPLE)
        set(CMAKE_GENERATOR "Eclipse CDT4 - Unix Makefiles")
        add_definitions(-DM2MO_LINUX_OS)
    elseif(APPLE)
        set(CMAKE_GENERATOR "Xcode")
        add_definitions(-DM2MO_MAC_OSX)
    elseif(WIN32)
        set(CMAKE_GENERATOR "Visual Studio 10")
        add_definitions(-DM2MO_WIN_OS)
    endif()
endif()
message("${M2MO_HEAD_MESSAGE}Building with CMAKE_GENERATOR='${CMAKE_GENERATOR}'")


#Boost
find_package(Boost COMPONENTS chrono filesystem serialization system thread)
if(Boost_FOUND)
    set(Boost_USE_STATIC_LIBS ON)
    include_directories(${Boost_INCLUDE_DIRS})
#    link_directories(${Boost_LIBRARY_DIRS})
endif()


include_directories(include)
add_subdirectory(src)
add_subdirectory(prog)


# Build test
if(M2MO_BUILD_TEST)
    # Test batteries is built using boost test framework, 
    # so if you dont have boost, tests can not be build
    if(Boost_FOUND)
        include(CTest)
        add_subdirectory(test)
    else()
        message("${M2MO_HEAD_MESSAGE} WARNING : You can build test only if you have boost library -- tests ARE NOT BUILD")
    endif()
endif()
