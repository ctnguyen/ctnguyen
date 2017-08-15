############################################################### #
#  Date             10/02/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#################################################################

## Include guard
if(Utilities_Include)
  return()
endif()
set(Utilities_Include TRUE)

#### Macro to simulate Map in Cmake
#    Usage 
#      ancoa_map_insert("MyMapName" "MyKeyName" "MyValue")
#      message(MyMapName_${MyKeyName} ${MyMapName_${MyKeyName}})
#
set(ANCOA_DEBUG_CMAKE_ANCOA_MAP_INSERT OFF)# Set to ON if want to debug
macro(ancoa_map_insert _MAPNAME _KEY _VALUE)
    set("${_MAPNAME}_${_KEY}" "${_VALUE}")
endmacro(ancoa_map_insert)

## Function get list of child directories (name only)
#     Given the absolute path to a parent directory
#     Populate the list of child directories name (no recurse)  
function(get_child_dirsname _dirnameList _absolutePath)
    file(GLOB childrenDirName RELATIVE ${_absolutePath} ${_absolutePath}/*)
    set(_nameList "")
    foreach(childDirName ${childrenDirName})
        if(IS_DIRECTORY ${_absolutePath}/${childDirName})
            list(APPEND _nameList ${childDirName})
        endif()
    endforeach()
    list(REMOVE_DUPLICATES _nameList)
    list(SORT _nameList)
    set(${_dirnameList} ${_nameList} PARENT_SCOPE)
endfunction()

#### Function get the site name from installer name
#    Installer name could be "Ancoa", "Ancoa_Server", "Ancoa_Client"
#    They all are of site "Ancoa"
#    The function write to the first variable_requires
#    Usage  
#        AncoaGetSiteName(site "Ancoa_Server")
#        message("===================${site}")
function(AncoaGetSiteName site installername)
    # installername ex Tradeweb Tradeweb_Client, Tradeweb_Server
    # they all give site = [Tradeweb]
    string(REPLACE "_" ";" _parts ${installername})
    list(LENGTH _parts _length)
    if(_length GREATER 1)
        list(GET _parts 0 _parts_0)
        set(${site} ${_parts_0} PARENT_SCOPE)
    else()
        set(${site} ${installername} PARENT_SCOPE)
    endif()
endfunction()


#### Function copy the dll when the lib is found
#    Usage 
#      ancoa_map_insert("MyMapName" "MyKeyName" "MyValue")
#
set(ANCOA_DEBUG_CMAKE_ANCOA_COPY_SHARED_LIB OFF)# Set to ON if want to debug
function(ancoa_copy_shared_lib _PATH_TO_FOUND_LIB _BuildConfig)
    if(ANCOA_DEBUG_CMAKE_ANCOA_COPY_SHARED_LIB)
        message(" -- Ancoa copy shared library ")
        message("      Lib File[${_PATH_TO_FOUND_LIB}]  Config[${_BuildConfig}] copy file:")
    endif()
    if(NOT EXISTS "${_PATH_TO_FOUND_LIB}")
        message(FATAL_ERROR "    File not exists [${_PATH_TO_FOUND_LIB}]")
    endif()
    get_filename_component(_DirPath ${_PATH_TO_FOUND_LIB} DIRECTORY)
    get_filename_component(_Name ${_PATH_TO_FOUND_LIB} NAME_WE)
    string(REPLACE "lib" "" _NameNoLib "${_Name}")# remove 'lib' from name
    
    if(WIN32)
        set(_RUNTIME_EXTENTION dll)
    else()
        set(_RUNTIME_EXTENTION so)
    endif()
    
    set(TrySharedLibToCopy1 "${_DirPath}/${_Name}.${_RUNTIME_EXTENTION}")
    set(TrySharedLibToCopy2 "${_DirPath}/${_NameNoLib}.${_RUNTIME_EXTENTION}")
    
    if(NOT EXISTS "${TrySharedLibToCopy1}" AND NOT EXISTS "${TrySharedLibToCopy2}")
        message(FATAL_ERROR "    File not exists [${TrySharedLibToCopy1}] , [${TrySharedLibToCopy2}]")
    endif()
    
    if(EXISTS "${TrySharedLibToCopy1}")
        set(SharedLibToCopy "${TrySharedLibToCopy1}")
    else()
        set(SharedLibToCopy "${TrySharedLibToCopy2}")
    endif()
    
    string(TOUPPER ${_BuildConfig} _OUTPUTCONFIG)
    if(DEFINED CMAKE_BUILD_TYPE)
        set(_COPY_DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    else()
        set(_COPY_DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_OUTPUTCONFIG}})
    endif()
        
    file(COPY ${SharedLibToCopy} DESTINATION ${_COPY_DESTINATION})
    if(WIN32)
        install(FILES ${SharedLibToCopy} DESTINATION "." COMPONENT AncoaFiles CONFIGURATIONS ${_BuildConfig})
    else()
        install(FILES ${SharedLibToCopy} DESTINATION "." COMPONENT AncoaFiles)
    endif()
    
    if(ANCOA_DEBUG_CMAKE_ANCOA_COPY_SHARED_LIB)
        message("      From : [${SharedLibToCopy}]")
        message("      To   : [${_COPY_DESTINATION}]")
    endif()
endfunction()