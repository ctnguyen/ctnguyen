############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################

## Include guard
if(BuildBoostExampleHelper_Include)
  return()
endif()
set(BuildBoostExampleHelper_Include TRUE)

set(BUILD_BOOST_EXAMPLE_HELPER_DEBUG OFF)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)
    message(STATUS "Preconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake] has been included")
endif()

if(NOT BUILD_BOOST_EXAMPLE)# -DBUILD_BOOST_EXAMPLE=ON in cmake command
    return()
endif()

#### Requirement : copy all example of a boost component to to ${CMAKE_CURRENT_SOURCE_DIR}/example_boost
####               For example  from $BOOST_ROOT/libs/log/example. Those example should be a single main.cpp file only
####               run cmake with option -DBUILD_BOOST_EXAMPLE=ON

### From the relative directory, cut the root part of the path             ##
### The rest split in to a list then concatenate to get the target name    ##
function(_getTargetName targetName filePath)
    get_filename_component(src_name ${filePath} NAME_WE)
    get_filename_component(src_dir ${filePath} DIRECTORY)
    
    string(REPLACE "${EXAMPLE_BOOST_DIR}/" "" _rel_path_file ${src_dir})
    string(REPLACE "/" ";" _list_sub_dir ${_rel_path_file})
    set(_list_sub_dir ${_list_sub_dir} ${src_name})
    string(REPLACE ";" "." _concat "${_list_sub_dir}")
    set(${targetName} ${_concat} PARENT_SCOPE)
endfunction()
##############################################################################

set(EXAMPLE_BOOST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/example_boost")

if(NOT EXISTS ${EXAMPLE_BOOST_DIR})
  return()
  message(FATAL_ERROR "Option to build boost example BUILD_BOOST_EXAMPLE was activated but no example was found. See BuildBoostExampleHelper.cmake")
endif()

# Get all files 
string(REPLACE "${CMAKE_SOURCE_DIR}/" "" _rel_path_dir ${EXAMPLE_BOOST_DIR})
file(GLOB_RECURSE _ALL_EXAMPLE_FILES ${EXAMPLE_BOOST_DIR}/*.cpp)

foreach(_src_file ${_ALL_EXAMPLE_FILES})
    _getTargetName(targetName ${_src_file})    
    add_executable(${targetName} ${_src_file})

    # If not a specific boost component example is specified, then link everything to every boost component
    if(NOT BOOST_EXAMPLE_COMPONENT)
        foreach(_boost_comp ${Project_Required_BOOST_COMPONENTS})
            target_link_libraries(${targetName} Boost::${_boost_comp})
        endforeach()        
    else()
        target_link_libraries(${targetName} Boost::${BOOST_EXAMPLE_COMPONENT})
    endif()
    ## Set folder structure in IDE
    target_compile_definitions(${targetName} PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
    set_property(TARGET ${targetName} PROPERTY FOLDER "Test/prototype/example_boost")
    
    if(MSVC)## Use cotire to accelerate the build
        set_target_properties(${targetName} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
    endif()
    cotire(${targetName})
    
    if(BUILD_BOOST_EXAMPLE_HELPER_DEBUG)
        message("... _src_file[${_src_file}]  targetName[${targetName}]")
    endif()
endforeach()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)
    message(STATUS "Postconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake] has been included")
endif()