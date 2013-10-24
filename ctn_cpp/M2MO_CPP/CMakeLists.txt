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

## include the project configuration file
if(EXISTS "${CMAKE_SOURCE_DIR}/user-config.cmake")
    include(${CMAKE_SOURCE_DIR}/user-config.cmake)
else()
    include(${CMAKE_SOURCE_DIR}/default-config.cmake)
endif()

## Setting the "normal" cmake generator, in case of special generator, modify user-config.cmake
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

## Setting warning compil messages
if(MSVC)
  set(CMAKE_CXX_WARNING_LEVEL 4)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W3" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
  endif(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4290 /wd4127 /wd4535")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-Wall -ansi -Wextra -fmessage-length=0")
  if(APPLE)
    set(CMAKE_CXX_FLAGS "-Wall -ansi -Wextra -fmessage-length=0")
  endif()
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3 -g" )
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()


## Boost
find_package(Boost COMPONENTS chrono filesystem serialization system thread)
if(Boost_FOUND)
    set(Boost_USE_STATIC_LIBS ON)
    include_directories(${Boost_INCLUDE_DIRS})
#    link_directories(${Boost_LIBRARY_DIRS})
endif()


## Copy configure file for getting absolute output path 
file(MAKE_DIRECTORY ${M2MO_OUTPUT_PATH})
configure_file("${CMAKE_SOURCE_DIR}/include/m2mo_path.h.in" "${CMAKE_SOURCE_DIR}/include/m2mo_path.h" @ONLY)


include_directories(include)
add_subdirectory(src)
add_subdirectory(prog)


## Build test
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


