############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################


if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)
    message(STATUS "Preconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake] has been included")
endif()

add_library(greet SHARED SharedDefineGreet.h greet.hpp greet.cpp)
target_compile_definitions(greet PUBLIC EXPORT_SHARED_GREET)

add_library(greet_ext SHARED greet_ext.cpp )
target_include_directories(greet_ext PUBLIC ${PYTHON_INCLUDE_DIRS})
target_link_libraries(greet_ext greet Boost::python ${PYTHON_LIBRARIES})

## Set folder structure in IDE
set_property(TARGET greet PROPERTY FOLDER "Test/prototype")
set_property(TARGET greet_ext PROPERTY FOLDER "Test/prototype")

InstallComponent(greet)
InstallComponent(greet_ext)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)
    message(STATUS "Postconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake] has been included")
endif()
