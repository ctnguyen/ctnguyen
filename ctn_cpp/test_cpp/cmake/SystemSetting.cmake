############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################

## Include guard
if(SystemSetting_Include)
  return()
endif()
set(SystemSetting_Include TRUE)

## The variable SOURCE_ROOT_DIR has to be set before calling this script
if(NOT SOURCE_ROOT_DIR)
    message("ERROR variable SOURCE_ROOT_DIR is not set")
    message(FATAL_ERROR "Variable SOURCE_ROOT_DIR should be set before calling SystemSetting.cmake")
endif()

set(RUNTIME_ROOT_DIR_DEV ${CMAKE_BINARY_DIR} CACHE INTERNAL "Root directory for runtime in development environment")
add_definitions(-DRUNTIME_ROOT_DIR_DEV=${RUNTIME_ROOT_DIR_DEV})
add_definitions(-DSOURCE_ROOT_DIR=${CMAKE_SOURCE_DIR})

if(NOT RUNTIME_STORAGE_DIRNAME)
    set(RUNTIME_STORAGE_DIRNAME STORAGE CACHE INTERNAL "Directory name used at runtime for all storage, helping to easy backup")
endif()
add_definitions(-DRUNTIME_STORAGE_DIRNAME=${RUNTIME_STORAGE_DIRNAME})
set(SWAP_EXPORT_VARIABLES "${SWAP_EXPORT_VARIABLES};RUNTIME_STORAGE_DIRNAME" CACHE INTERNAL "List of important variable to export" FORCE)##Append to the list

if(NOT RUNTIME_DB_DIRNAME)
    set(RUNTIME_DB_DIRNAME Data CACHE INTERNAL "Database directory name used at runtime")
endif()
add_definitions(-DRUNTIME_DB_DIRNAME=${RUNTIME_DB_DIRNAME})
set(SWAP_EXPORT_VARIABLES "${SWAP_EXPORT_VARIABLES};RUNTIME_DB_DIRNAME" CACHE INTERNAL "List of important variable to export" FORCE)##Append to the list

set(CPP_INCLUDE_GENERATED ${RUNTIME_ROOT_DIR_DEV}/generated CACHE INTERNAL "Directories containing all generated file for cpp")
file(MAKE_DIRECTORY ${CPP_INCLUDE_GENERATED})

## Create runtime directories
if(DEV_BUILD)
    set(_RUNTIME_DB_DIR "${RUNTIME_ROOT_DIR_DEV}/${RUNTIME_STORAGE_DIRNAME}/${RUNTIME_DB_DIRNAME}")
    file(MAKE_DIRECTORY ${_RUNTIME_DB_DIR})
endif()

function(print_system_info)
    message("")
    message(" ================ BUILD SYSTEM INFO  ================= ")
    message("  - Machine info")
    message("      SYSTEM_BUILD_ARCHI [${SYSTEM_BUILD_ARCHI}]")
    message("      SYSTEM_OS          [${SYSTEM_OS}]")
    message("")
    message("  - Directories info")
    message("      BACKEND_SOURCE_DIR      [${BACKEND_SOURCE_DIR}]")
    message("      FRONTEND_SOURCE_DIR     [${FRONTEND_SOURCE_DIR}]")
    message("      RUNTIME_ROOT_DIR_DEV    [${RUNTIME_ROOT_DIR_DEV}]")
    message("      RUNTIME_STORAGE_DIRNAME [${RUNTIME_STORAGE_DIRNAME}]")
    message("      RUNTIME_DB_DIRNAME      [${RUNTIME_DB_DIRNAME}]")
    message("      CPP_INCLUDE_GENERATED   [${CPP_INCLUDE_GENERATED}]")
    message("")
    message("  - Environment variables :")
    message("      BOOST_ROOT  [$ENV{BOOST_ROOT}]")
    message("")
    message(" ===================================================== ")
    message("")
    
endfunction(print_system_info)