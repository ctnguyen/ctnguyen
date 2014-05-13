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
find_package(Boost 1.55.0 COMPONENTS filesystem regex)
if(Boost_FOUND)
    set(Boost_USE_STATIC_LIBS ON)
    include_directories(${Boost_INCLUDE_DIRS})
#    link_directories(${Boost_LIBRARY_DIRS})
endif()

## QuantLib Finding Library
## You have to rightly specify your QUANTLIB_ROOT environment variable
include_directories($ENV{QUANTLIB_ROOT})
link_directories($ENV{QUANTLIB_ROOT}/lib)
if(WIN32)
#set(QuantLib_LIBRAIRES "QuantLib-vc110-mt.lib QuantLib-vc110-mt-gd.lib")
set(QuantLib_LIBRAIRES "QuantLib-vc110-mt-gd.lib")
endif()

## Debug cmake messages
message("Environment variable has specified BOOST_ROOT[$ENV{BOOST_ROOT}]")
message("Environment variable has specified QUANTLIB_ROOT[$ENV{QUANTLIB_ROOT}]")
message("Boost_LIBRARY : [${Boost_LIBRARIES}]")


add_subdirectory(LMM) 


