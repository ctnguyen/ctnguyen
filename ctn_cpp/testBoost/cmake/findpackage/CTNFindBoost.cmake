############################################################### #
#  Date             10/02/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                             
#################################################################
## Include guard
if(CTNFindBoost_Include)
  return()
endif()
set(CTNFindBoost_Include TRUE)

#### From imported .lib of boost library, get the .dll path
function(ctnGetDllFromLib _libPathInput _dllPathOutput)
    if(NOT EXISTS ${_libPathInput})
        message(FATAL_ERROR "ctnGetDllFromLib : file [${_libPathInput}] doesn't exists")
    endif()

    get_filename_component(_libPathInput_WE ${_libPathInput} NAME_WE)
    get_filename_component(_libPathInput_DIR ${_libPathInput} DIRECTORY)
    set(_file_dll_path_we ${_libPathInput_DIR}/${_libPathInput_WE})
    set(_file_dll_path ${_libPathInput_DIR}/${_libPathInput_WE}.dll)
    if(NOT EXISTS ${_file_dll_path})
        message(WARNING "ctnGetDllFromLib : file [${_file_dll_path}] doesn't exists alongside [${_libPathInput}]")
        set(${_dllPathOutput} ${_libPathInput}-NOTFOUND PARENT_SCOPE)
    else()
        set(${_dllPathOutput} ${_file_dll_path} PARENT_SCOPE)
    endif()
endfunction()

## _Qt5Target should not contain Boost::
## For example Boost::chrono, call ctnCopyImportedBoost(chrono ".")
function(ctnCopyImportedBoost _BoostTarget _subFolder)
    ## Copy boost dll/so to build folder.
    
    get_property(_boost_IMPORTED_LOCATION TARGET Boost::${_Boost_Comp} PROPERTY IMPORTED_LOCATION)
    get_property(_boost_IMPORTED_LOCATION_DEBUG TARGET Boost::${_Boost_Comp} PROPERTY IMPORTED_LOCATION_DEBUG)
    get_property(_boost_IMPORTED_LOCATION_RELEASE TARGET Boost::${_Boost_Comp} PROPERTY IMPORTED_LOCATION_RELEASE)
    
    if(NOT CMAKE_BUILD_TYPE)# MSVC
        if(EXISTS ${_boost_IMPORTED_LOCATION})
            ctnGetDllFromLib(${_boost_IMPORTED_LOCATION} _boost_IMPORTED_LOCATION_DLL)
            file(COPY ${_boost_IMPORTED_LOCATION_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_subFolder})
            install(FILES ${_boost_IMPORTED_LOCATION_DLL} DESTINATION ${_subFolder} COMPONENT thirdLIB)
        endif()
        if(EXISTS ${_boost_IMPORTED_LOCATION_RELEASE})
            ctnGetDllFromLib(${_boost_IMPORTED_LOCATION_RELEASE} _boost_IMPORTED_LOCATION_RELEASE_DLL)
            file(COPY ${_boost_IMPORTED_LOCATION_RELEASE_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/${_subFolder})
            install(FILES ${_boost_IMPORTED_LOCATION_RELEASE_DLL} DESTINATION ${_subFolder} COMPONENT thirdLIB)
        endif()
        if(EXISTS ${_boost_IMPORTED_LOCATION_DEBUG})
            ctnGetDllFromLib(${_boost_IMPORTED_LOCATION_DEBUG} _boost_IMPORTED_LOCATION_DEBUG_DLL)
            file(COPY ${_boost_IMPORTED_LOCATION_DEBUG_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/${_subFolder})
            install(FILES ${_boost_IMPORTED_LOCATION_DEBUG_DLL} DESTINATION ${_subFolder} COMPONENT thirdLIB)
        endif()
    else()
        # CMAKE_BUILD_TYPE is defined and have value
        set(COPY_DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        set(_CMakeBuildType ${CMAKE_BUILD_TYPE})
        string(TOUPPER ${_CMakeBuildType} _OUTPUTCONFIG)
        string(COMPARE EQUAL ${_OUTPUTCONFIG} "DEBUG" isDebugBuild)
        if(isDebugBuild)
            if(_boost_IMPORTED_LOCATION_DEBUG)
                file(COPY ${_boost_IMPORTED_LOCATION_DEBUG} DESTINATION ${COPY_DESTINATION}/${_subFolder})
                install(FILES ${_boost_IMPORTED_LOCATION_DEBUG} DESTINATION ${_subFolder} COMPONENT thirdLIB)
            elseif(_boost_IMPORTED_LOCATION_RELEASE)
                file(COPY ${_boost_IMPORTED_LOCATION_RELEASE} DESTINATION ${COPY_DESTINATION}/${_subFolder})
                install(FILES ${_boost_IMPORTED_LOCATION_RELEASE} DESTINATION ${_subFolder} COMPONENT thirdLIB)
            else()
                file(COPY ${_boost_IMPORTED_LOCATION} DESTINATION ${COPY_DESTINATION}/${_subFolder})
                install(FILES ${_boost_IMPORTED_LOCATION} DESTINATION ${_subFolder} COMPONENT thirdLIB)
            endif()
        else()
            if(_boost_IMPORTED_LOCATION_RELEASE)
                file(COPY ${_boost_IMPORTED_LOCATION_RELEASE} DESTINATION ${COPY_DESTINATION}/${_subFolder})
                install(FILES ${_boost_IMPORTED_LOCATION_RELEASE} DESTINATION ${_subFolder} COMPONENT thirdLIB)
            else()
                file(COPY ${_boost_IMPORTED_LOCATION} DESTINATION ${COPY_DESTINATION}/${_subFolder})
                install(FILES ${_boost_IMPORTED_LOCATION} DESTINATION ${_subFolder} COMPONENT thirdLIB)
            endif()
        endif()            
    endif()
endfunction()

function(ctnCorrectImportedSharedBoost _BoostTarget) ## Need to do only for Windows
    ## Standard FindBoost does not do the job correctly
    ## It need to improve here
    ## On windows : imported location should be .dll, and imported implib are .lib
    ## On Linux   : imported location should real file, not the symlink of the file
    if(WIN32) 
        set(_TYPES "" _DEBUG _RELEASE)
        foreach(_type ${_TYPES})
            get_property(_boost_IMPORTED_LOCATION${_type} TARGET Boost::${_Boost_Comp} PROPERTY IMPORTED_LOCATION${_type})
            get_filename_component(_boost_IMPORTED_LOCATION${_type}_WE ${_boost_IMPORTED_LOCATION${_type}} NAME_WE)
            get_filename_component(_boost_IMPORTED_LOCATION${_type}_DIR ${_boost_IMPORTED_LOCATION${_type}} DIRECTORY)
            set(_boost_IMPORTED_LOCATION${_type}_FILEPATH ${_boost_IMPORTED_LOCATION${_type}_DIR}/${_boost_IMPORTED_LOCATION${_type}_WE}) # full file path without extension
            set(_boost_IMPORTED_LOCATION${_type}_CORRECTED ${_boost_IMPORTED_LOCATION${_type}_FILEPATH}.dll)
            set_target_properties(Boost::${_Boost_Comp} PROPERTIES 
                                  IMPORTED_IMPLIB${_type} ${_boost_IMPORTED_LOCATION${_type}}
                                  IMPORTED_LOCATION${_type} ${_boost_IMPORTED_LOCATION${_type}_CORRECTED})
        endforeach()
    else()#Unix
        set(_TYPES "" _DEBUG _RELEASE)
        foreach(_type ${_TYPES})
            get_property(_boost_IMPORTED_LOCATION${_type} TARGET Boost::${_Boost_Comp} PROPERTY IMPORTED_LOCATION${_type})
            get_filename_component(_boost_IMPORTED_LOCATION${_type}_CORRECTED ${_boost_IMPORTED_LOCATION${_type}} REALPATH)# get the real path of the lib, not the path to symlink
            set_target_properties(Boost::${_Boost_Comp} PROPERTIES 
                                  IMPORTED_LOCATION${_type} ${_boost_IMPORTED_LOCATION${_type}_CORRECTED})
        endforeach()
    endif()
endfunction()
## Before building boost, need to install bzip2-devel, python-devel
## build boost 
## Build command on linux
## sudo ./b2 --with=all link=shared,static runtime-link=shared
##  Build command on Windows (same?)
##
if(CUSTOM_CTN_BOOST_ROOT)
    set(BOOST_ROOT ${CUSTOM_CTN_BOOST_ROOT})
elseif(DEFINED ENV{BOOST_ROOT})
    set(BOOST_ROOT $ENV{BOOST_ROOT})
elseif(CTN_FRAMEWORKS_BOOST_ROOT)
    set(BOOST_ROOT ${CTN_FRAMEWORKS_BOOST_ROOT})
endif()

find_package(Threads) ## find threads first might fix a warning when looking for boost thread

message("  --  try to find Boost in [${BOOST_ROOT}]")
## http://stackoverflow.com/questions/6646405/how-do-you-add-boost-libraries-in-cmakelists-txt
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

## dont forget to add 
# target_compile_definitions(yourtarget PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
# target_link_libraries(${projNAME} Boost::your_boost_component)

## Add a required component here  ======================
set(Ctn_Required_BOOST_COMPONENTS
    chrono
    date_time
    iostreams
    filesystem
    regex
    serialization
    system
    thread
    unit_test_framework
)

find_package(Boost 1.61 COMPONENTS ${Ctn_Required_BOOST_COMPONENTS} REQUIRED)

### Correct the import functionality of boost by cmake. 
### ?????? DID THAT TO REPLICATE THE IMPORTED Boost::target look similar to Qt5::target, but doesnt work for boost. So leave it as it is
#foreach(_Boost_Comp ${Ctn_Required_BOOST_COMPONENTS})
#    ctnCorrectImportedSharedBoost(${_Boost_Comp})
#endforeach()

foreach(_Boost_Comp ${Ctn_Required_BOOST_COMPONENTS})
    ctnCopyImportedBoost(${_Boost_Comp} ".")
endforeach()


message("")