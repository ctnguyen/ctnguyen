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

project(LunaLib) 

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

add_subdirectory(LMM) 


