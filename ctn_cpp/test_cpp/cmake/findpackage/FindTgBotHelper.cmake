############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################
## Include guard
if(FindTgBotHelper_Include)
  return()
endif()
set(FindTgBotHelper_Include TRUE)

set(DEBUG_FIND_TgBot_HELPER OFF)# Set to ON if want to debug

################################################################################################
################################################################################################
## User need to set environment variable TGBOT_ROOT pointing to the root of TgBot library
## All header files should be in       $TGBOT_ROOT/include/tgbot
## All static lib files should be in   $TGBOT_ROOT/lib

## Make sure to use the file TgBot.CMakeLists.txt in $ROOT/cmake/findpackage to build and install TgBot

#.rst:
# FindTgBot
# ---------
#
# Try to find TgBot
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines :prop_tgt:`IMPORTED` target ``TgBot::TgBot``, if
# TgBot has been found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ::
#
#   TgBot_FOUND - system has TgBot
#   TgBot_INCLUDE_DIR - the TgBot include directory
#   TgBot_LIBRARIES - Link these to use TgBot
#   TgBot_NEED_PREFIX - this is set if the functions are prefixed with BZ2_
#   TgBot_VERSION_STRING - the version of TgBot found (since CMake 2.8.8)

if(DEFINED ENV{BOOST_ROOT}) ## iF ENV{BOOST_ROOT} is defined, add a list of hint paths to lookup here
    set(_HINT_TgBot_ROOT_BY_BOOST)
	set(_BOOST_ROOT_ $ENV{BOOST_ROOT})
	get_filename_component(_HINT_INSTALL_PREFIX ${_BOOST_ROOT_}/.. ABSOLUTE)
	set(_HINT_TgBot_DIRNAME TgBot tgbot-cpp-master tgbot)
    foreach(_HINT_DIRNAME ${_HINT_TgBot_DIRNAME})
		get_filename_component(_HINT_PATH_BY_BOOST ${_HINT_INSTALL_PREFIX}/${_HINT_DIRNAME} ABSOLUTE)
		set(_HINT_TgBot_ROOT_BY_BOOST ${_HINT_TgBot_ROOT_BY_BOOST} ${_HINT_PATH_BY_BOOST})
    endforeach()
endif()

## HINTS PATH put all here
set(_TgBot_PATHS PATHS "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\TgBot;InstallPath];$ENV{TGBOT_ROOT};${_HINT_TgBot_ROOT_BY_BOOST}")
if(DEBUG_FIND_TgBot_HELPER)
    message("List of hints path to find TgBot")
    foreach(_HINT_PATH ${_TgBot_PATHS})
        message(" [${_HINT_PATH}]")
    endforeach()
endif()
find_path(_Installed_TgBot_INCLUDE_DIR 
          NAMES tgbot/tgbot.h
          PATHS ${_TgBot_PATHS}
          PATH_SUFFIXES include)

if(_Installed_TgBot_INCLUDE_DIR)
    set(TgBot_INCLUDE_DIR ${_Installed_TgBot_INCLUDE_DIR})
endif()
          
if (NOT TgBot_LIBRARIES)
    find_library(TgBot_LIBRARY_RELEASE NAMES TgBot PATHS ${_TgBot_PATHS} PATH_SUFFIXES lib)
    find_library(TgBot_LIBRARY_DEBUG NAMES TgBotd PATHS ${_TgBot_PATHS} PATH_SUFFIXES lib)

    include(SelectLibraryConfigurations)
    SELECT_LIBRARY_CONFIGURATIONS(TgBot)
endif ()

set(TgBot_VERSION "UNKNOWN")

# handle the QUIETLY and REQUIRED arguments and set TgBot_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TgBot REQUIRED_VARS TgBot_LIBRARIES TgBot_INCLUDE_DIR)

if (TgBot_FOUND)
   include(CheckSymbolExists)
   include(CMakePushCheckState)
   cmake_push_check_state()
   set(CMAKE_REQUIRED_QUIET ${TgBot_FIND_QUIETLY})
   set(CMAKE_REQUIRED_INCLUDES ${TgBot_INCLUDE_DIR})
   set(CMAKE_REQUIRED_LIBRARIES ${TgBot_LIBRARIES})
   #CHECK_SYMBOL_EXISTS(BZ2_bzCompressInit "bzlib.h" TgBot_NEED_PREFIX)
   cmake_pop_check_state()

    if(NOT TARGET TgBot::TgBot)
      add_library(TgBot::TgBot UNKNOWN IMPORTED)
      set_target_properties(TgBot::TgBot PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${TgBot_INCLUDE_DIRS}")

      if(TgBot_LIBRARY_RELEASE)
        set_property(TARGET TgBot::TgBot APPEND PROPERTY
          IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(TgBot::TgBot PROPERTIES
          IMPORTED_LOCATION_RELEASE "${TgBot_LIBRARY_RELEASE}")
      endif()

      if(TgBot_LIBRARY_DEBUG)
        set_property(TARGET TgBot::TgBot APPEND PROPERTY
          IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(TgBot::TgBot PROPERTIES
          IMPORTED_LOCATION_DEBUG "${TgBot_LIBRARY_DEBUG}")
      endif()

      if(NOT TgBot_LIBRARY_RELEASE AND NOT TgBot_LIBRARY_DEBUG)
        set_property(TARGET TgBot::TgBot APPEND PROPERTY
          IMPORTED_LOCATION "${TgBot_LIBRARY}")
      endif()
    endif()
endif ()

mark_as_advanced(TgBot_INCLUDE_DIR)
################################################################################################
################################################################################################

if(NOT TgBot_FOUND)
    message("  -- Cmake cannot find TgBot in [${CMAKE_INSTALL_PREFIX}]")
    message("  -- You need to put TgBot library in the folder structure [${CMAKE_INSTALL_PREFIX}]")
    message("          [${CMAKE_INSTALL_PREFIX}]")
    message("               include/tgbot : *.h *.hpp")
    message("               lib           : *.a *.lib *.dll *.so")
endif()

if(DEBUG_FIND_TgBot_HELPER)
    message("                 TgBot_FOUND [${TgBot_FOUND}]")
    message("           TgBot_INCLUDE_DIR [${TgBot_INCLUDE_DIR}]")
    message("             TgBot_LIBRARIES [${TgBot_LIBRARIES}]")
    message("           TgBot_NEED_PREFIX [${TgBot_NEED_PREFIX}]")
    message("        TgBot_VERSION_STRING [${TgBot_VERSION_STRING}]")
endif()
message("")
