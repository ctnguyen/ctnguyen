#################################################
#   chithanhnguyen.math@gmail.com               #
#   QuantLib hello world                        #
#   - cmake                                     #
#   - boost                                     #
#   - QuantLib                                  #
#                                               #
#   09.Mai.2014                                 #
#################################################

#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 2.8)

project(QuantLibHelloWorld) 

## Boost Finding Library
## You have to rightly specify your BOOST_ROOT environment variable
find_package(Boost 1.55.0 COMPONENTS date_time filesystem system)
if(Boost_FOUND)
    set(Boost_USE_STATIC_LIBS ON)
    include_directories(${Boost_INCLUDE_DIRS})
#    link_directories(${Boost_LIBRARY_DIRS})
endif()

## QuantLib Finding Library
## You have to rightly specify your QUANTLIB_ROOT environment variable
#include_directories($ENV{QUANTLIB_ROOT})
#link_directories($ENV{QUANTLIB_ROOT}/lib)

##########################################
## tempo for Mac os
## include dir is /usr/local/opt/QuantLib/include/
## lib dir is     /usr/local/opt/QuantLib/lib
#include_directories(/usr/local/opt/QuantLib/include/)
#link_directories(/usr/local/opt/QuantLib/lib)

## File test QuantLib function copied from example
#  QuantLib\Examples\Bonds\bond.cpp

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/config/")
find_package(QuantLib)
if(QuantLib_FOUND)
    #set(QuantLib_USE_STATIC_LIBS ON)
    include_directories(${QuantLib_INCLUDE_DIR})
	#    link_directories(${QuantLib_LIBRARY_DIR})
endif()


add_executable(qlHello main.cpp)

# Works for Mac Install
target_link_libraries(qlHello ${QuantLib_LIBRARY})

## Debug cmake messages
message("Environment variable has specified BOOST_ROOT[$ENV{BOOST_ROOT}]")
message("Environment variable has specified QUANTLIB_ROOT[$ENV{QUANTLIB_ROOT}]")
message("Boost_LIBRARY : [${Boost_LIBRARIES}]")
message("Boost_INCLUDE_DIRS[${Boost_INCLUDE_DIRS}]")
message("Boost_LIBRARY_DIRS[${Boost_LIBRARY_DIRS}]")

