#################################################
#   chithanhnguyen.math@gmail.com               #
#                                               #
#   Lunalogic intership project 2014            #
#   LIBOR Market Model                          #
#   Technologies:                               #
#   - cmake                                     #
#   - boost                                     #
#   - QuantLib                                  #
#                                               #
#   14.Mai.2014                                 #
#################################################

#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 2.8)

project(LunaLMM)
 
include(CTest)
#enable_testing()

## disable unecessary warnings
if(MSVC)
	add_definitions( "/W3 /D_CRT_SECURE_NO_WARNINGS /wd4996 /wd4535 /nologo" )
endif()

## force using of C++11X on Unix machine
if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
endif()
## Boost Finding Library
## You have to rightly specify your BOOST_ROOT environment variable
#find_package(Boost 1.55.0 COMPONENTS filesystem regex)
find_package(Boost)
if(Boost_FOUND)
    set(Boost_USE_STATIC_LIBS ON)
    include_directories(${Boost_INCLUDE_DIRS})
#    link_directories(${Boost_LIBRARY_DIRS})
endif()

## QuantLib Finding Library
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/config/")
find_package(QuantLib)
if(QuantLib_FOUND)
    #set(QuantLib_USE_STATIC_LIBS ON)
    include_directories(${QuantLib_INCLUDE_DIR})
	#    link_directories(${QuantLib_LIBRARY_DIR})
endif()


### Runtime path will be used for storing input files required when executing programs
### This path is dependent of OS, for windows, it's "\", for unix it's "/"
### In cmake, set always with forward space, it will by replaced by backward automatically if windows
###

# copy all data from source directory into binary directory in order to execute and retreive output
file(COPY "${CMAKE_SOURCE_DIR}/data/" DESTINATION "${CMAKE_BINARY_DIR}/data/")

set(LMM_OUTPUT_RUNTIMEPATH "${CMAKE_BINARY_DIR}/data/output/")
set(LMM_DATA_RUNTIMEPATH "${CMAKE_BINARY_DIR}/data/input/")

file(MAKE_DIRECTORY ${LMM_OUTPUT_RUNTIMEPATH})

### change "/" to be "\\" in the runtime path for RvsB_path.h
if(WIN32)
    string(REGEX REPLACE "/" "\\\\\\\\" LMM_OUTPUT_RUNTIMEPATH "${LMM_OUTPUT_RUNTIMEPATH}")
    string(REGEX REPLACE "/" "\\\\\\\\" LMM_DATA_RUNTIMEPATH "${LMM_DATA_RUNTIMEPATH}") 
endif()
configure_file("${CMAKE_SOURCE_DIR}/config/generic_path.h.in" "${CMAKE_SOURCE_DIR}/LMM/generic_path.h" @ONLY)

# add the root source directory for include directory
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(src) 
add_subdirectory(test)
add_subdirectory(proc) 


