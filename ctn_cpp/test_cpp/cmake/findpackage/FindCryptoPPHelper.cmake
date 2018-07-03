############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################
## Include guard
if(FindCryptoPPHelper_Include)
  return()
endif()
set(FindCryptoPPHelper_Include TRUE)

set(DEBUG_FIND_CRYPTOPP_HELPER OFF)# Set to ON if want to debug

################################################################################################
################################################################################################
## User need to set environment variable CRYPTOPP_ROOT pointing to the root of CryptoPP library
## Or put the the crypto installation alongside with BOOST_ROOT 
##    crypto565       <-- cmake will install the built Crypto++ from here
##    boost_x_x_x     <-- cmake find package helper will base on BOOST_ROOT or 


# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindCryptoPP
# ---------
#
# Try to find CryptoPP
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines :prop_tgt:`IMPORTED` target ``CryptoPP::CryptoPP``, if
# CryptoPP has been found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ::
#
#   CRYPTOPP_FOUND - system has CryptoPP
#   CRYPTOPP_INCLUDE_DIR - the CryptoPP include directory
#   CRYPTOPP_LIBRARIES - Link these to use CryptoPP
#   CRYPTOPP_NEED_PREFIX - this is set if the functions are prefixed with BZ2_
#   CRYPTOPP_VERSION_STRING - the version of CryptoPP found (since CMake 2.8.8)

if(DEFINED ENV{BOOST_ROOT}) ## iF ENV{BOOST_ROOT} is defined, add a list of hint paths to lookup here
    set(_HINT_CRYPTOPP_ROOT_BY_BOOST)
	set(_BOOST_ROOT_ $ENV{BOOST_ROOT})
	get_filename_component(_HINT_INSTALL_PREFIX ${_BOOST_ROOT_}/.. ABSOLUTE)
	set(_HINT_CRYPTOPP_DIRNAME crypto565 cryptopp CryptoPP crypto++ Crypto++)
    foreach(_HINT_DIRNAME ${_HINT_CRYPTOPP_DIRNAME})
		get_filename_component(_HINT_PATH_BY_BOOST ${_HINT_INSTALL_PREFIX}/${_HINT_DIRNAME} ABSOLUTE)
		set(_HINT_CRYPTOPP_ROOT_BY_BOOST ${_HINT_CRYPTOPP_ROOT_BY_BOOST} ${_HINT_PATH_BY_BOOST})
    endforeach()
endif()

## HINTS PATH put all here
set(_CRYPTOPP_PATHS PATHS "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\CryptoPP;InstallPath];$ENV{CRYPTOPP_ROOT};${_HINT_CRYPTOPP_ROOT_BY_BOOST}")
if(DEBUG_FIND_CRYPTOPP_HELPER)
    message("List of hints path to find CryptoPP")
    foreach(_HINT_PATH ${_CRYPTOPP_PATHS})
        message(" [${_HINT_PATH}]")
    endforeach()
endif()
find_path(_Installed_CRYPTOPP_INCLUDE_DIR 
          NAMES cryptopp/cryptlib.h
          PATHS ${_CRYPTOPP_PATHS}
          PATH_SUFFIXES include)

if(_Installed_CRYPTOPP_INCLUDE_DIR)
    set(CRYPTOPP_INCLUDE_DIR ${_Installed_CRYPTOPP_INCLUDE_DIR})
endif()
          
if (NOT CRYPTOPP_LIBRARIES)
    find_library(CRYPTOPP_LIBRARY_RELEASE NAMES staticcrypto++ staticcrypto++.a crypto++ crypto++.so cryptlib cryptopp PATHS ${_CRYPTOPP_PATHS} PATH_SUFFIXES lib)
    find_library(CRYPTOPP_LIBRARY_DEBUG NAMES staticcrypto++d staticcrypto++d.a crypto++d crypto++.so cryptlibd cryptoppd PATHS ${_CRYPTOPP_PATHS} PATH_SUFFIXES lib)

    include(SelectLibraryConfigurations)
    SELECT_LIBRARY_CONFIGURATIONS(CRYPTOPP)
endif ()

set(_CRYPTOPP_VERSION_HEADER ${CRYPTOPP_INCLUDE_DIR}/cryptopp/config.h)
if (CRYPTOPP_INCLUDE_DIR AND EXISTS ${_CRYPTOPP_VERSION_HEADER})

    file(STRINGS ${_CRYPTOPP_VERSION_HEADER} _CRYPTOPP_VERSION_TMP REGEX "^#define CRYPTOPP_VERSION[ \t]+[0-9]+$")
    
    string(REGEX REPLACE "^#define CRYPTOPP_VERSION[ \t]+([0-9]+)" "\\1" _CRYPTOPP_VERSION_TMP ${_CRYPTOPP_VERSION_TMP})

    string(REGEX REPLACE "([0-9]+)[0-9][0-9]" "\\1" CRYPTOPP_VERSION_MAJOR ${_CRYPTOPP_VERSION_TMP})
    string(REGEX REPLACE "[0-9]([0-9])[0-9]" "\\1" CRYPTOPP_VERSION_MINOR ${_CRYPTOPP_VERSION_TMP})
    string(REGEX REPLACE "[0-9][0-9]([0-9])" "\\1" CRYPTOPP_VERSION_PATCH ${_CRYPTOPP_VERSION_TMP})

    set(CRYPTOPP_VERSION_COUNT 3)
    set(CRYPTOPP_VERSION ${CRYPTOPP_VERSION_MAJOR}.${CRYPTOPP_VERSION_MINOR}.${CRYPTOPP_VERSION_PATCH})
endif ()

# handle the QUIETLY and REQUIRED arguments and set CryptoPP_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CryptoPP
                                  REQUIRED_VARS CRYPTOPP_LIBRARIES CRYPTOPP_INCLUDE_DIR
                                  VERSION_VAR CRYPTOPP_VERSION_STRING)

if (CRYPTOPP_FOUND)
   include(CheckSymbolExists)
   include(CMakePushCheckState)
   cmake_push_check_state()
   set(CMAKE_REQUIRED_QUIET ${CryptoPP_FIND_QUIETLY})
   set(CMAKE_REQUIRED_INCLUDES ${CRYPTOPP_INCLUDE_DIR})
   set(CMAKE_REQUIRED_LIBRARIES ${CRYPTOPP_LIBRARIES})
   #CHECK_SYMBOL_EXISTS(BZ2_bzCompressInit "bzlib.h" CRYPTOPP_NEED_PREFIX)
   cmake_pop_check_state()

    if(NOT TARGET CryptoPP::CryptoPP)
      add_library(CryptoPP::CryptoPP UNKNOWN IMPORTED)
      set_target_properties(CryptoPP::CryptoPP PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CRYPTOPP_INCLUDE_DIRS}")

      if(CRYPTOPP_LIBRARY_RELEASE)
        set_property(TARGET CryptoPP::CryptoPP APPEND PROPERTY
          IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(CryptoPP::CryptoPP PROPERTIES
          IMPORTED_LOCATION_RELEASE "${CRYPTOPP_LIBRARY_RELEASE}")
      endif()

      if(CRYPTOPP_LIBRARY_DEBUG)
        set_property(TARGET CryptoPP::CryptoPP APPEND PROPERTY
          IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(CryptoPP::CryptoPP PROPERTIES
          IMPORTED_LOCATION_DEBUG "${CRYPTOPP_LIBRARY_DEBUG}")
      endif()

      if(NOT CRYPTOPP_LIBRARY_RELEASE AND NOT CRYPTOPP_LIBRARY_DEBUG)
        set_property(TARGET CryptoPP::CryptoPP APPEND PROPERTY
          IMPORTED_LOCATION "${CRYPTOPP_LIBRARY}")
      endif()
    endif()
endif ()

mark_as_advanced(CRYPTOPP_INCLUDE_DIR)
################################################################################################
################################################################################################

if(NOT CRYPTOPP_FOUND)
    message("  -- Cmake cannot find CryptoPP in [${CMAKE_INSTALL_PREFIX}]")
    message("  -- You need to put CryptoPP library in the folder structure [${CMAKE_INSTALL_PREFIX}]")
    message("          [${CMAKE_INSTALL_PREFIX}]")
    message("               include : *.h *.hpp")
    message("               lib     : *.a *.lib *.dll *.so")
endif()

if(DEBUG_FIND_CRYPTOPP_HELPER)
    message("                 CRYPTOPP_FOUND [${CRYPTOPP_FOUND}]")
    message("           CRYPTOPP_INCLUDE_DIR [${CRYPTOPP_INCLUDE_DIR}]")
    message("             CRYPTOPP_LIBRARIES [${CRYPTOPP_LIBRARIES}]")
    message("           CRYPTOPP_NEED_PREFIX [${CRYPTOPP_NEED_PREFIX}]")
    message("        CRYPTOPP_VERSION_STRING [${CRYPTOPP_VERSION_STRING}]")
endif()
message("")