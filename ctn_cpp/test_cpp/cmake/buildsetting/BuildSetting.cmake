############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################

## Include guard
if(BuildSetting_Include)
  return()
endif()
set(BuildSetting_Include TRUE)

if(NOT DEBUG_BUILD_SETTING_FOLDERS)
    set(DEBUG_BUILD_SETTING_FOLDERS OFF)# Set to ON if want to debug
endif()

macro(SetCompilationOptions)
    ## Set common compile options
    set(CMAKE_CXX_STANDARD 14)#Use C++14 ## TODO : change to C++ 17 when visual studio 17 support C++17
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF) # Do not use extension
    set(CMAKE_DEBUG_POSTFIX d)
    cmake_policy(SET CMP0057 NEW)# USE IN_LIST functionality, example: if(${var} IN_LIST MYVAR_LIST)
    if (MSVC)
      add_definitions(/wd4251 /wd4244 -D_SCL_SECURE_NO_WARNINGS)
      add_definitions(-DNOMINMAX)# Remove ambigious of min and max in windows
      add_definitions(-DUNICODE)
    endif()
    
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)#
    set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "_CMakePredefinedTarget" )
endmacro()

#### DEFINE BUILD FOLDER ACCORDING TO THE BUILD CONFIGURATRION AND BUILD TYPE
#### Based on the defined 
####   ${SYSTEM_BUILD_ARCHI} 
####   ${CMAKE_CONFIGURATION_TYPES}
####   ${CMAKE_BUILTYPE}
function(SetBuildFolders)

    if(NOT _POST_BUID_DIRECTORY_PROPERTIES)
        set(_POST_BUID_DIRECTORY_PROPERTIES)
    endif()
    set(_FILE_TYPES RUNTIME LIBRARY ARCHIVE)

    if(NOT DEFINED SYSTEM_BUILD_ARCHI)
        message("  SetBuildFolders : variable [SYSTEM_BUILD_ARCHI] is not defined")
        message(FATAL_ERROR "On Windows, [SYSTEM_BUILD_ARCHI] should be defined x64 or x86")
    endif()

    ### Setting for IDE that can build both Debug and Release in one solution, i.e Visual Studio, XCode
    foreach( _OutputConfig ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${_OutputConfig} _OUTPUTCONFIG)
        string(TOLOWER ${_OutputConfig} _outputconfig)

        set(_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${SYSTEM_BUILD_ARCHI}/${_outputconfig}")
        foreach(FileType ${_FILE_TYPES})
            set(CMAKE_${FileType}_OUTPUT_DIRECTORY_${_OUTPUTCONFIG} "${_OUTPUT_PATH}" CACHE PATH "Default path for runtime ouput directory" FORCE)
            list(APPEND _POST_BUID_DIRECTORY_PROPERTIES ${FileType}_OUTPUT_DIRECTORY_${_OUTPUTCONFIG})
        endforeach()
    endforeach()

    ### Setting if a single build type is specified ## Typically Linux Makefile
    if(DEFINED CMAKE_BUILD_TYPE)
        if(CMAKE_BUILD_TYPE)
            set(_CMakeBuildType ${CMAKE_BUILD_TYPE})
        else()
            set(_CMakeBuildType Release)
        endif()
        string(TOUPPER ${_CMakeBuildType} _CMAKE_BUILD_TYPE)
        string(TOLOWER ${_CMakeBuildType} _cmake_build_type)

        set(_MAIN_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${SYSTEM_BUILD_ARCHI}/${_cmake_build_type}")
        foreach(FileType ${_FILE_TYPES})
            set(CMAKE_${FileType}_OUTPUT_DIRECTORY "${_MAIN_OUTPUT_PATH}" CACHE PATH "Default path for runtime ouput directory" FORCE)
            list(APPEND _POST_BUID_DIRECTORY_PROPERTIES ${FileType}_OUTPUT_DIRECTORY)
        endforeach()

        set(_BuildTypeTagList "Release" "Debug")
        foreach(_Build_Type_Tag ${_BuildTypeTagList})
            string(TOUPPER ${_Build_Type_Tag} _BUILD_TYPE_TAG)
            string(TOLOWER ${_Build_Type_Tag} _build_type_tag)
            foreach(FileType ${_FILE_TYPES})
                set(_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${SYSTEM_BUILD_ARCHI}/${_build_type_tag}")
                set(CMAKE_${FileType}_OUTPUT_DIRECTORY_${_BUILD_TYPE_TAG} "${_OUTPUT_PATH}" CACHE PATH "Default path for runtime ouput directory" FORCE)
                list(APPEND _POST_BUID_DIRECTORY_PROPERTIES ${FileType}_OUTPUT_DIRECTORY_${_BUILD_TYPE_TAG})
            endforeach()
        endforeach()

    endif()
    
    set(_POST_BUID_DIRECTORY_PROPERTIES ${_POST_BUID_DIRECTORY_PROPERTIES} CACHE INTERNAL "List of output directories properties" FORCE)
     
    if(DEBUG_BUILD_SETTING_FOLDERS)
        foreach( _VAR ${_POST_BUID_DIRECTORY_PROPERTIES})
            message(" SetBuildFolders [CMAKE_${_VAR}]=[${CMAKE_${_VAR}}]")
        endforeach()
    endif()
endfunction()

function(SetBuildVersion)
    if(NOT BACKEND_VERSION_MAJOR)
        set(BACKEND_VERSION_MAJOR "1" CACHE INTERNAL "Application backend major version" FORCE)
    endif()
    if(NOT BACKEND_VERSION_MINOR)
        set(BACKEND_VERSION_MINOR "0" CACHE INTERNAL "Application backend minor version" FORCE)
    endif()
    if(NOT BACKEND_VERSION_PATCH)
        set(BACKEND_VERSION_PATCH "1" CACHE INTERNAL "Application backend patch version" FORCE)
    endif()
    
    ### get git branch and commit hash
    ### http://xit0.org/2013/04/cmake-use-git-branch-and-commit-details-in-project/
    # Get the current working branch
    execute_process(
      COMMAND git rev-parse --abbrev-ref HEAD
      WORKING_DIRECTORY ${SOURCE_ROOT_DIR}
      OUTPUT_VARIABLE _SourceBranch
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(SOURCE_GIT_BRANCH ${_SourceBranch} CACHE INTERNAL "Source branch" FORCE)
    
    # Get the latest abbreviated commit hash of the working branch
    execute_process(
      COMMAND git log -1 --format=%h
      WORKING_DIRECTORY ${SOURCE_ROOT_DIR}
      OUTPUT_VARIABLE _Source_Commit_Hash
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(SOURCE_GIT_COMMIT_HASH ${_Source_Commit_Hash} CACHE INTERNAL "Source commit hash" FORCE)
    
    # Get the latest commit datetime
    execute_process(
      COMMAND git log -1 --date=short --pretty=format:%ci
      WORKING_DIRECTORY ${SOURCE_ROOT_DIR}
      OUTPUT_VARIABLE _Source_commit_datetime
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(SOURCE_GIT_COMMIT_DATETIME ${_Source_commit_datetime} CACHE INTERNAL "Source commit datetime" FORCE)
    
    # Get the build date time
    string(TIMESTAMP _build_datetime_UTD "%d-%m-%Y %H:%M:%S")
    set(BUILD_DATETIME_UTC ${_build_datetime_UTD} CACHE INTERNAL "Build datetime UTC" FORCE)
    
    #### Generate version C++  #####
    set(CTN_VERSION_HPP_IN ${SOURCE_ROOT_DIR}/cmake/buildsetting/CTNVersion.hpp.in CACHE INTERNAL "Template File for CTN version config")
    set(CTN_VERSION_HPP ${CPP_INCLUDE_GENERATED}/CTNVersion.hpp CACHE INTERNAL "HPP File for CTN version config")
    configure_file(${CTN_VERSION_HPP_IN} ${CTN_VERSION_HPP})
endfunction()

function(SetBuildVariables)
    if(NOT BUILD_WITH_COTIRE)
        set(BUILD_WITH_COTIRE ON CACHE INTERNAL "Use cotire to enhance compilation time" FORCE)
    endif()    
    set(CTN_EXPORT_VARIABLES "${CTN_EXPORT_VARIABLES};BUILD_WITH_COTIRE" CACHE INTERNAL "List of important variable to export" FORCE)##Append to the list
    
    if(DEV_BUILD)    
      set(BUILD_ALL_TESTS ON CACHE INTERNAL "Enable building all tests" FORCE)
      add_definitions(-DDEV_BUILD) ## That will help to partition the code of dev and prod
      add_definitions(-DTEST_PRIVATE_METHOD) ## Set flag to test all private methods
    else()
      if(NOT BUILD_ALL_TESTS)
        set(BUILD_ALL_TESTS OFF)
      else()
        set(BUILD_ALL_TESTS OFF)
      endif()
    endif()
    set(CTN_EXPORT_VARIABLES "${CTN_EXPORT_VARIABLES};DEV_BUILD" CACHE INTERNAL "List of important variable to export" FORCE)##Append to the list

    #if(NOT DEV_BUILD)
        set(LOG_TO_CONSOLE ON CACHE INTERNAL "Flag allowing to log to console" FORCE)
        set(LOG_DEBUG_INFO ON CACHE INTERNAL "Flag allowing extra information to log ease the debugging" FORCE)
    #endif()

    if(LOG_TO_CONSOLE)
        add_definitions(-DLOG_TO_CONSOLE)
    endif()

    if(LOG_DEBUG_INFO)
        add_definitions(-DLOG_DEBUG_INFO)
    endif()
    set(SWAP_EXPORT_VARIABLES "${SWAP_EXPORT_VARIABLES};LOG_TO_CONSOLE" CACHE INTERNAL "List of important variable to export" FORCE)##Append to the list
    set(SWAP_EXPORT_VARIABLES "${SWAP_EXPORT_VARIABLES};LOG_DEBUG_INFO" CACHE INTERNAL "List of important variable to export" FORCE)##Append to the list
    
endfunction()

function(print_buildsetting_info)
    message(" ========= BUILD SETTING INFO  ========== ")
    if(DEV_BUILD)
        message("")
        message("  BuilType : [DEV]")
    else() # Production build
        message("")
        message(STATUS "WARNING : BuilType : [PROD]")
    endif()
    if(BUILD_WITH_COTIRE)
        message("  Use cotire [YES]")
    else()
        message("  Use cotire [NO]")
    endif()
    message("  CTN_VERSION_HPP    [${CTN_VERSION_HPP}]")
    message("  CTN_VERSION_HPP_IN [${CTN_VERSION_HPP_IN}]")
    message("  BUILD_DATETIME_UTC    [${BUILD_DATETIME_UTC}]")
    message("")
    message("  - Source version : ")
    message("      SOURCE_GIT_BRANCH          [${SOURCE_GIT_BRANCH}]")
    message("      SOURCE_GIT_COMMIT_HASH     [${SOURCE_GIT_COMMIT_HASH}]")
    message("      SOURCE_GIT_COMMIT_DATETIME [${SOURCE_GIT_COMMIT_DATETIME}]")
    
    message("")
    message("  - Backend version : ")
    message("      BACKEND_VERSION_MAJOR [${BACKEND_VERSION_MAJOR}]")
    message("      BACKEND_VERSION_MINOR [${BACKEND_VERSION_MINOR}]")
    message("      BACKEND_VERSION_PATCH [${BACKEND_VERSION_PATCH}]")
    message(" ======================================== ")
    message("")
    
endfunction()