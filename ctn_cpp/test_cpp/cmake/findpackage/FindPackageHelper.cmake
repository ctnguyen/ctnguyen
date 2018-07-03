############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################
## Include guard
if(FindPackageHelper_Include)
  return()
endif()
set(FindPackageHelper_Include TRUE)

if(NOT DEBUG_FIND_PACKAGE_HELPER)
    set(DEBUG_FIND_PACKAGE_HELPER OFF)# Set to ON if want to debug
endif()

# Check if the shared library is library 
#
function(checkIfImported _Lib _Component)
    if(NOT TARGET ${_Lib}::${_Component})
        message(FATAL_ERROR "FindPackageHelper.cmake::checkIfImported TARGET[${_Lib}::${_Component}] doesn't exist")
    endif()
    
    if(DEBUG_FIND_PACKAGE_HELPER)
        message(STATUS "FindPackageHelper.cmake::checkIfImported(${_Lib}::${_Component}) OK")
    endif()
endfunction()

# On linux, to make things easier, let the software link directly to the library instead of using the symlink
#   _Lib could be Boost, Qt5
#   _Component is the component of the library
#   _BUILD_TYPE_TAG could be empty, _DEBUG, _RELEASE
#   Example Boost::system, Qt5::Core ...
#      makeTargetNoSymlink(Boost system _RELEASE)
#      makeTargetNoSymlink(Qt5 Core _DEBUG)
function(makeTargetNoSymlink _Lib _Component _BUILD_TYPE_TAG)
    if(APPLE OR NOT UNIX)
         return()
    endif()

    checkIfImported("${_Lib}" "${_Component}")

    if(DEBUG_FIND_PACKAGE_HELPER)
        message(STATUS "FindPackageHelper.cmake::makeTargetNoSymlink(${_Lib}::${_Component} ${_BUILD_TYPE_TAG})")
    endif()
    set(_BUILD_TYPE_TAG_LIST "" "_RELEASE" "_DEBUG")
    foreach(_BUILD_TYPE_TAG ${_BUILD_TYPE_TAG_LIST})
        get_property(_lib_IMPORTED_LOCATION${_BUILD_TYPE_TAG} TARGET ${_Lib}::${_Component} PROPERTY IMPORTED_LOCATION${_BUILD_TYPE_TAG})
        if(_lib_IMPORTED_LOCATION${_BUILD_TYPE_TAG})
            get_filename_component(_solved_symlink_file ${_lib_IMPORTED_LOCATION${_BUILD_TYPE_TAG}} REALPATH)
            if(EXISTS ${_solved_symlink_file})
                set_target_properties(${_Lib}::${_Component} PROPERTIES IMPORTED_LOCATION${_BUILD_TYPE_TAG} ${_solved_symlink_file})
            else()
                message(FATAL_ERROR "FindPackageHelper.cmake::makeTargetNoSymlink, file [${_solved_symlink_file}] doesn't exist")
            endif()
        endif()
    endforeach()
endfunction()



# On linux, to make things easier, let the software link directly to the library instead of using the symlink
#   _Lib could be Boost, Qt5
#   _Component is the component of the library
#   _BUILD_TYPE_TAG could be empty, _DEBUG, _RELEASE
#   Example Qt5::Core ...
#      copyImportedSharedLibrary("Qt5" Core ".")
#      copyImportedSharedLibrary("Qt5" QPSQLDriverPlugin "sqldrivers")
#
# To use this function , the SHARED library should be imported properly
# - On Windows/Mac : 
#     IMPORTED_IMPLIB_${<CONFIG>} should be the .lib file
#     IMPORTED_LOCATION_${<CONFIG>} should be the .dll/.dylib file
# - on Linux
#     IMPORTED_LOCATION_${<BUILD_TYPE>} should be the .so file
function(copyImportedSharedLibrary  _Lib _Component _subFolder)
    checkIfImported("${_Lib}" "${_Component}")
    
    ## Copy Qt dll/so to build folder.
    get_property(_3rdLIB_IMPORTED_LOCATION TARGET ${_Lib}::${_Component} PROPERTY IMPORTED_LOCATION)
    get_property(_3rdLIB_IMPORTED_LOCATION_DEBUG TARGET ${_Lib}::${_Component} PROPERTY IMPORTED_LOCATION_DEBUG)
    get_property(_3rdLIB_IMPORTED_LOCATION_RELEASE TARGET ${_Lib}::${_Component} PROPERTY IMPORTED_LOCATION_RELEASE)

    if(NOT CMAKE_BUILD_TYPE)# MSVC
        if(_3rdLIB_IMPORTED_LOCATION)
            file(COPY ${_3rdLIB_IMPORTED_LOCATION} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_subFolder})
            install(FILES ${_3rdLIB_IMPORTED_LOCATION} DESTINATION ${_subFolder} COMPONENT Files)
        endif()
        if(_3rdLIB_IMPORTED_LOCATION_RELEASE)
            file(COPY ${_3rdLIB_IMPORTED_LOCATION_RELEASE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/${_subFolder})
            install(FILES ${_3rdLIB_IMPORTED_LOCATION_RELEASE} DESTINATION ${_subFolder} COMPONENT Files)
        endif()
        if(_3rdLIB_IMPORTED_LOCATION_DEBUG)
            file(COPY ${_3rdLIB_IMPORTED_LOCATION_DEBUG} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/${_subFolder})
        endif()
    else()
        # CMAKE_BUILD_TYPE is defined and have value
        set(COPY_DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    if(_3rdLIB_IMPORTED_LOCATION_RELEASE)
        file(COPY ${_3rdLIB_IMPORTED_LOCATION_RELEASE} DESTINATION ${COPY_DESTINATION}/${_subFolder})
        install(FILES ${_3rdLIB_IMPORTED_LOCATION_RELEASE} DESTINATION ${_subFolder} COMPONENT Files)
    elseif(_3rdLIB_IMPORTED_LOCATION_DEBUG)
        file(COPY ${_3rdLIB_IMPORTED_LOCATION_DEBUG} DESTINATION ${COPY_DESTINATION}/${_subFolder})
        install(FILES ${_3rdLIB_IMPORTED_LOCATION_DEBUG} DESTINATION ${_subFolder} COMPONENT Files)
    else()
        file(COPY ${_3rdLIB_IMPORTED_LOCATION} DESTINATION ${COPY_DESTINATION}/${_subFolder})
        install(FILES ${_3rdLIB_IMPORTED_LOCATION} DESTINATION ${_subFolder} COMPONENT Files)
    endif()
    endif()
endfunction()
