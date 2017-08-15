#################################################################
#  Date             14/08/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                              
#################################################################
## Include guard
if(SetBuildFolders_Include)
  return()
endif()
set(SetBuildFolders_Include TRUE)


if(NOT DEBUG_CTN_SET_BUILD_FOLDERS)
    set(DEBUG_CTN_SET_BUILD_FOLDERS OFF)# Set to ON if want to debug
endif()
#### DEFINE BUILD FOLDER ACCORDING TO THE BUILD CONFIGURATRION AND BUILD TYPE
#### Based on the defined 
####   ${CTN_BUILD_ARCHI} 
####   ${CMAKE_CONFIGURATION_TYPES}
####   ${CMAKE_BUILTYPE}

function(CTNSetBuildFolders)

    if(NOT POST_BUID_DIRECTORY_PROPERTIES)
        set(POST_BUID_DIRECTORY_PROPERTIES)
    endif()

    if(NOT DEFINED CTN_BUILD_ARCHI)
        message("  CTNSetBuildFolders : variable [CTN_BUILD_ARCHI] is not defined")
        message(FATAL_ERROR "On Windows, [CTN_BUILD_ARCHI] should be defined x64 or x86")
    endif()

    ### Setting for IDE that can build both Debug and Release in one solution, i.e Visual Studio, XCode
    foreach( _OutputConfig ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${_OutputConfig} _OUTPUTCONFIG)
        string(TOLOWER ${_OutputConfig} _outputconfig)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/${CTN_BUILD_ARCHI}/${_outputconfig}" CACHE PATH "Default path for runtime ouput directory" FORCE)
        list(APPEND POST_BUID_DIRECTORY_PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${_OUTPUTCONFIG})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${_OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/${CTN_BUILD_ARCHI}/${_outputconfig}" CACHE PATH "Default path for runtime ouput directory" FORCE)
        list(APPEND POST_BUID_DIRECTORY_PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${_OUTPUTCONFIG})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${_OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/${CTN_BUILD_ARCHI}/${_outputconfig}" CACHE PATH "Default path for runtime ouput directory" FORCE)
        list(APPEND POST_BUID_DIRECTORY_PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${_OUTPUTCONFIG})
    endforeach()

    ### Setting if a single build type is specified
    if(DEFINED CMAKE_BUILD_TYPE)
        if(CMAKE_BUILD_TYPE)
            set(_CMakeBuildType ${CMAKE_BUILD_TYPE})
        else()
            set(_CMakeBuildType Release)
        endif()
        string(TOUPPER ${_CMakeBuildType} _CMAKE_BUILD_TYPE)
        string(TOLOWER ${_CMakeBuildType} _cmake_build_type)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CTN_BUILD_ARCHI}/${_cmake_build_type}" CACHE PATH "Default path for runtime ouput directory" FORCE)
        list(APPEND POST_BUID_DIRECTORY_PROPERTIES RUNTIME_OUTPUT_DIRECTORY)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CTN_BUILD_ARCHI}/${_cmake_build_type}" CACHE PATH "Default path for runtime ouput directory" FORCE)
        list(APPEND POST_BUID_DIRECTORY_PROPERTIES LIBRARY_OUTPUT_DIRECTORY)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CTN_BUILD_ARCHI}/${_cmake_build_type}" CACHE PATH "Default path for runtime ouput directory" FORCE)
        list(APPEND POST_BUID_DIRECTORY_PROPERTIES ARCHIVE_OUTPUT_DIRECTORY)
        
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_CMAKE_BUILD_TYPE} "${CMAKE_BINARY_DIR}/${CTN_BUILD_ARCHI}/${_cmake_build_type}" CACHE PATH "Default path for runtime ouput directory" FORCE)
        list(APPEND POST_BUID_DIRECTORY_PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${_CMAKE_BUILD_TYPE})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${_CMAKE_BUILD_TYPE} "${CMAKE_BINARY_DIR}/${CTN_BUILD_ARCHI}/${_cmake_build_type}" CACHE PATH "Default path for runtime ouput directory" FORCE)
        list(APPEND POST_BUID_DIRECTORY_PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${_CMAKE_BUILD_TYPE})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${_CMAKE_BUILD_TYPE} "${CMAKE_BINARY_DIR}/${CTN_BUILD_ARCHI}/${_cmake_build_type}" CACHE PATH "Default path for runtime ouput directory" FORCE)
        list(APPEND POST_BUID_DIRECTORY_PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${_CMAKE_BUILD_TYPE})
    endif()
    
    set(POST_BUID_DIRECTORY_PROPERTIES ${POST_BUID_DIRECTORY_PROPERTIES} CACHE INTERNAL "List of output directories properties" FORCE)
    
    if(DEBUG_CTN_SET_BUILD_FOLDERS)
    foreach( _VAR ${POST_BUID_DIRECTORY_PROPERTIES})
        message(" Set [CMAKE_${_VAR}]=[${${_VAR}}]")
    endforeach()
    endif()

endfunction()

macro(CTNSetPluginOutput targetName pluginDir) ## pluginDir is relative dir from build folder
    if(NOT TARGET ${targetName})
        message(FATAL_ERROR "CTNSetBuildFolders::CTNSetPluginOutput [${targetName}] IS NOT A TARGET")
    endif()
    
    if(NOT POST_BUID_DIRECTORY_PROPERTIES)
        message(FATAL_ERROR "CTNSetBuildFolders::CTNSetPluginOutput POST_BUID_DIRECTORY_PROPERTIES is not set")
    endif()
    
    foreach( _DIRECTORY_PROPERTY ${POST_BUID_DIRECTORY_PROPERTIES})
        set_target_properties(${targetName} PROPERTIES ${_DIRECTORY_PROPERTY} "${CMAKE_${_DIRECTORY_PROPERTY}}/${pluginDir}")
        if(DEBUG_CTN_SET_BUILD_FOLDERS)
            message(" Set POST_BUID_DIRECTORY_PROPERTIES for target [${targetName}]")
            message("     ${_DIRECTORY_PROPERTY}=[${CMAKE_${_DIRECTORY_PROPERTY}}/${pluginDir}]")
        endif()
    endforeach()
endmacro()