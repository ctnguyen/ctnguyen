############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################
## Include guard
if(FindBoostHelper_Include)
  return()
endif()
set(FindBoostHelper_Include TRUE)

if(NOT DEBUG_FIND_BOOST_HELPER)
    set(DEBUG_FIND_BOOST_HELPER OFF)# Set to ON if want to debug
endif()
include(${SOURCE_ROOT_DIR}/cmake/findpackage/FindPackageHelper.cmake)

## dont forget to add 
# target_compile_definitions(yourtarget PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
# target_link_libraries(yourtarget Boost::your_boost_component)

## Copy lib file to the given destination (relative path).
## The file can be of wrong extention .lib, .a, the function will convert to the right extention
## _BUILD_TYPE_TAG can be "" "_DEBUG" "_RELEASE" indicating build type tag to contatenate
function(copyAndInstallSharedBoostLib _libFilePath _subFolder _BUILD_TYPE_TAG)
    if(${DEBUG_FIND_BOOST_HELPER})
        message("== FindBoostHelper.cmake::copyAndInstallSharedBoostLib")
        message("      call with  _libFilePath[${_libFilePath}] _subFolder[${_subFolder}] _BUILD_TYPE_TAG[${_BUILD_TYPE_TAG}]")
    endif()

    if(${SYSTEM_OS} STREQUAL windows)
        string(REPLACE ".lib" ".dll" _modifiedLibFilePath ${_libFilePath})
    elseif(${SYSTEM_OS} STREQUAL mac)
        string(REPLACE ".a" ".dylib" _modifiedLibFilePath ${_libFilePath})
    else() # linux
        string(REPLACE ".a" ".so" _modifiedLibFilePath ${_libFilePath})
    endif()
    
    set(_PATH_OF_COPY_DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY${_BUILD_TYPE_TAG}}/${_subFolder})
    if(${DEBUG_FIND_BOOST_HELPER})
        message("== FindBoostHelper.cmake  copy file from [${_modifiedLibFilePath}] to [${_PATH_OF_COPY_DESTINATION}]")
        message("                            install file [${_modifiedLibFilePath}] as component Myfiles to [${_subFolder}] ")
    endif()
    file(COPY ${_modifiedLibFilePath} DESTINATION ${_PATH_OF_COPY_DESTINATION})
    install(FILES ${_modifiedLibFilePath} DESTINATION ${_subFolder} COMPONENT Files)
endfunction()

## _BoostTarget should not contain Boost::
## For example Boost::chrono, call copyImportedSharedBoost(chrono ".")
function(copyImportedSharedBoost _Boost_Comp _subFolder)
    set(_BUILD_TYPE_TAG_LIST "" "_RELEASE" "_DEBUG")
    foreach(_BUILD_TYPE_TAG ${_BUILD_TYPE_TAG_LIST})
	    ## Solve the symplinks on Linux
        if(UNIX AND NOT APPLE)#Linux
     	    makeTargetNoSymlink(Boost ${_Boost_Comp} ${_BUILD_TYPE_TAG})
        endif()

        get_property(_boost_IMPORTED_LOCATION${_BUILD_TYPE_TAG} TARGET Boost::${_Boost_Comp} PROPERTY IMPORTED_LOCATION${_BUILD_TYPE_TAG})
        if(_boost_IMPORTED_LOCATION${_BUILD_TYPE_TAG})
            copyAndInstallSharedBoostLib(${_boost_IMPORTED_LOCATION${_BUILD_TYPE_TAG}} ${_subFolder} ${_BUILD_TYPE_TAG})
        endif()
    endforeach()
endfunction()

## Before building boost, need to install bzip2-devel, python-devel
## build boost 
## Build command on linux
## sudo ./b2 --with=all link=shared,static runtime-link=shared
##  Build command on Windows (same?)
##
if(CUSTOM_BOOST_ROOT)
    set(BOOST_ROOT ${CUSTOM_BOOST_ROOT})
elseif(DEFINED ENV{BOOST_ROOT})
    set(BOOST_ROOT $ENV{BOOST_ROOT})
endif()

find_package(Threads) ## find threads first might fix a warning when looking for boost thread

message(STATUS "Try to find Boost in [${BOOST_ROOT}]")
## http://stackoverflow.com/questions/6646405/how-do-you-add-boost-libraries-in-cmakelists-txt
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED) # Recommended by the doc as to better use of Boost::filesystem (2018/02/13 version 3)

## Setting used to work for unit test, set it here to avoid all missmatch when a certain component conflict with tests when it comes to linking with boost
add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-DBOOST_ALL_DYN_LINK)

if(WIN32) ## Hack to fix conflict between Boost::asio and Boost::log
    ## https://svn.boost.org/trac10/ticket/12974?replyto=description
    add_definitions(-D_WIN32_WINNT=0x0A00)
endif()
## Add a required component here  ======================
if(NOT Project_Required_BOOST_COMPONENTS)
    set(Project_Required_BOOST_COMPONENTS
        atomic
        chrono
        context
        coroutine
        date_time
        filesystem
        log
        log_setup
        program_options
        random
        regex
        system
        thread
        unit_test_framework
        CACHE INTERNAL "List of required boost components"
    )
    if(${DEBUG_FIND_BOOST_HELPER})
        message("== FindBoostHelper.cmake  Project_Required_BOOST_COMPONENTS[${Project_Required_BOOST_COMPONENTS}]")
    endif()
else()
    if(${DEBUG_FIND_BOOST_HELPER})
        message("==  FindBoostHelper.cmake : Project_Required_BOOST_COMPONENTS variable is already set [${Project_Required_BOOST_COMPONENTS}]")
    endif()
endif()

find_package(PythonInterp)
find_package(PythonLibs)
if(PYTHONLIBS_FOUND)
    set(Project_Required_BOOST_COMPONENTS ${Project_Required_BOOST_COMPONENTS} python)
endif()

find_package(Boost ${boost_MINIMUM_REQUIRED} COMPONENTS ${Project_Required_BOOST_COMPONENTS} REQUIRED)

foreach(_Boost_Comp ${Project_Required_BOOST_COMPONENTS})
    copyImportedSharedBoost(${_Boost_Comp} ".")
endforeach()
