#################################################################
#  Date             14/08/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                            
#################################################################

## Include guard
if(SetNonConsoleAppProperty_Include)
  return()
endif()
set(SetNonConsoleAppProperty_Include TRUE)

if(NOT DEBUG_CTN_SET_NONCONSOLE_APP_PROPERTY)
    set(DEBUG_CTN_SET_NONCONSOLE_APP_PROPERTY ON)# Set to ON if want to debug
endif()

#  This function call to set the target of type GUI application to not open the console
#
## See 
##     https://stackoverflow.com/questions/2752792/whats-the-equivalent-of-gccs-mwindows-option-in-cmake
##     https://stackoverflow.com/questions/2139637/hide-console-of-windows-application
function(CTNSetNonConsoleAppProperty targetName)
    if(DEBUG_CTN_SET_NONCONSOLE_APP_PROPERTY)
        message(STATUS "CTNSetNonConsoleAppProperty : Set property for Non Console App [${targetName}]")
    endif()

    if(MSVC)
        set_target_properties(${targetName} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
        set_target_properties(${targetName} PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
    else()
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            target_compile_options(${targetName} PRIVATE -mwindows)
        endif()
    endif()

endfunction()