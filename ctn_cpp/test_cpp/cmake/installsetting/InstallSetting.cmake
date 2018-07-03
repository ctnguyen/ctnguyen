############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################
## Include guard
if(installsetting_Include)
  return()
endif()
set(installsetting_Include TRUE)

if(NOT DEBUG_INSTALL_SETTING)
    set(DEBUG_INSTALL_SETTING ON)# Set to ON if want to debug
endif()

function(InstallIncludeFiles _FileList _CompName)
    foreach(_file ${_FileList})
        install(FILES ${_file} DESTINATION API/Include/${_CompName} COMPONENT API)
    endforeach()
endfunction()

function(InstallComponent _CompName)
    install(TARGETS ${_CompName} RUNTIME DESTINATION "." LIBRARY DESTINATION "." ARCHIVE DESTINATION "API/lib" COMPONENT Core)
endfunction()

function(InstallPlugin _PluginName)
    install(TARGETS ${_PluginName} RUNTIME DESTINATION "Plugins" LIBRARY DESTINATION "Plugins" ARCHIVE DESTINATION "Plugins" COMPONENT "${_PluginName}")
endfunction()

function(InstallProgram _ProgName)
    install(TARGETS ${_ProgName} RUNTIME DESTINATION "." LIBRARY DESTINATION "." ARCHIVE DESTINATION "." COMPONENT Application)
endfunction()

#### Setting allow all executable, shared libraries are relocatable (relative RPATH)
function(setRelocatability)
    if(WIN32)
        ## Hardcoded redistributable files to copy to runtime directory, installer can be simply done by zipping built directory
        ## TODO make it correctly done through cpack (install prerequist functioinality of cpack)
        set(HARDCODED_MSVC_REDISTRIBUTABLE_FILES
        "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Redist/MSVC/14.11.25415/onecore/x64/Microsoft.VC141.CRT/msvcp140.dll"
        "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Redist/MSVC/14.11.25415/onecore/x64/Microsoft.VC141.CRT/vcruntime140.dll"
        )
        foreach(_Runtime_file ${HARDCODED_MSVC_REDISTRIBUTABLE_FILES})
            message("    Cmake setRelocatability Copy")
            message("      FILE : [${_Runtime_file}]")
            message("      TO   : [${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}]")
            file(COPY ${_Runtime_file} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
            message("    Cmake setRelocatability Copy")
            message("      FILE : [${_Runtime_file}]")
            message("      TO   : [${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}]")
            file(COPY ${_Runtime_file} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
        endforeach()
        
        set(_PRODUCTION_TESTS_RUNNER "${CMAKE_SOURCE_DIR}/cmake/installsetting/runProductionTests.bat")
        message("    Cmake setRelocatability Copy")
        message("      FILE : [${_PRODUCTION_TESTS_RUNNER}]")
        message("      TO   : [${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}]")
        file(COPY ${_PRODUCTION_TESTS_RUNNER} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
        message("    Cmake setRelocatability Copy")
        message("      FILE : [${_PRODUCTION_TESTS_RUNNER}]")
        message("      TO   : [${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}]")
        file(COPY ${_PRODUCTION_TESTS_RUNNER} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
        return()## This setting apply to Unix only
    endif()

    if(NOT APPLE)## Linux
        set(CMAKE_SKIP_BUILD_RPATH OFF CACHE BOOL "hello")
        set(CMAKE_BUILD_WITH_INSTALL_RPATH ON CACHE BOOL "hello")
        set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON CACHE BOOL "hello")
        
        if(CMAKE_INSTALL_RPATH)
            set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:$ORIGIN" CACHE PATH "Relative RPATH setting")
        else()
            set(CMAKE_INSTALL_RPATH "$ORIGIN" CACHE PATH "Relative RPATH setting")
        endif()
    #else()## Mac OS X can be slightly different, TODO
    endif()

    if(DEBUG_INSTALL_SETTING)
        message("          CMAKE_SKIP_BUILD_RPATH            [${CMAKE_SKIP_BUILD_RPATH}]")
        message("          CMAKE_BUILD_WITH_INSTALL_RPATH    [${CMAKE_BUILD_WITH_INSTALL_RPATH}]")
        message("          CMAKE_INSTALL_RPATH               [${CMAKE_INSTALL_RPATH}]")
        message("          CMAKE_INSTALL_RPATH_USE_LINK_PATH [${CMAKE_INSTALL_RPATH_USE_LINK_PATH}]")
    endif()
endfunction()

function(getExportVariableSetting stringVar)
    set(_string "")
    foreach(_var ${CTN_EXPORT_VARIABLES})
        set(_varName ${_var})
        if(${_varName})
            set(_varValue ${${_varName}})
            set(_string "${_string}\nset(${_varName} ${${_varName}} CACHE INTERNAL \"Predefined variable for build\")")
        else()
            set(_string "${_string}\n# ${_varName} -- not defined ---------------------")
        endif()
    endforeach()
    set(${stringVar} "${_string}" PARENT_SCOPE) 
endfunction()

function(copyExportBuildVariable)
    list(REMOVE_DUPLICATES CTN_EXPORT_VARIABLES)
    getExportVariableSetting(PRECONFIG_SETTING)
    #message(${PRECONFIG_SETTING})
    set(EXPORT_CONFIG_TEMPLATE_FILE "${CMAKE_SOURCE_DIR}/cmake/installsetting/ExportConfig.cmake.in")

    if(WIN32)
        set(IMPORT_CONFIG_FILE_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/ImportConfig.cmake")
        configure_file(${EXPORT_CONFIG_TEMPLATE_FILE} ${IMPORT_CONFIG_FILE_DEBUG})
        set(IMPORT_CONFIG_FILE_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/ImportConfig.cmake")
        configure_file(${EXPORT_CONFIG_TEMPLATE_FILE} ${IMPORT_CONFIG_FILE_RELEASE})
    else()
        set(IMPORT_CONFIG_FILE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ImportConfig.cmake")
        configure_file(${EXPORT_CONFIG_TEMPLATE_FILE} ${IMPORT_CONFIG_FILE})
    endif()
endfunction()

function(print_export_variables)
    message("=== List of export variable stored in [CTN_EXPORT_VARIABLES] ===")
    foreach(_var ${CTN_EXPORT_VARIABLES})
        set(_varName ${_var})
        if(${_varName})
            set(_varValue ${${_varName}})
        else()
            set(_varValue "NOT DEFINED")
        endif()
        message("    Name[${_varName}] : value[${_varValue}]")
    endforeach()
endfunction()
