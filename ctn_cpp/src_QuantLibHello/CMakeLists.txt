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
find_package(Boost)
if(Boost_FOUND)
    set(Boost_USE_STATIC_LIBS ON)
    include_directories(${Boost_INCLUDE_DIRS})
#    link_directories(${Boost_LIBRARY_DIRS})
endif()

## QuantLib Finding Library
## You have to rightly specify your QUANTLIB_ROOT environment variable
include_directories($ENV{QUANTLIB_ROOT})
link_directories($ENV{QUANTLIB_ROOT}/lib)

## File test QuantLib function copied from example
#  QuantLib\Examples\Bonds\bond.cpp
add_executable(qlHello main.cpp)


## Debug cmake messages
message("Environment variable has specified BOOST_ROOT[$ENV{BOOST_ROOT}]")
message("Environment variable has specified QUANTLIB_ROOT[$ENV{QUANTLIB_ROOT}]")




