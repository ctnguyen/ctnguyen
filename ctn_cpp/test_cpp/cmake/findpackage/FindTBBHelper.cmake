############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################
## Include guard
if(FindTBBHelper_Include)
  return()
endif()
set(FindTBBHelper_Include TRUE)

if(NOT DEBUG_FIND_TBB_HELPER)
    set(DEBUG_FIND_TBB_HELPER OFF)# Set to ON if want to debug
endif()
include(${SOURCE_ROOT_DIR}/cmake/findpackage/FindPackageHelper.cmake)

## dont forget to add 
# target_link_libraries(yourtarget TBB::your_TBB_component)

if(NOT DEFINED ENV{TBB_DIR})
    message(WARNING "Failed to find TBB in Config mode")
    message(WARNING "Environment variable [TBB_DIR] need to be defined and point to the root of the installed TBB library")
    message(WARNING "Not found environment variable TBB_DIR")
endif()

## Add a required component here  ======================
if(NOT Project_Required_TBB_COMPONENTS)
    set(Project_Required_TBB_COMPONENTS
        tbb
        tbbmalloc
        #tbbproxy
        #tbbmalloc_proxy
        CACHE INTERNAL "List of required TBB components"
    )
else()
    if(${DEBUG_FIND_TBB_HELPER})
        message("==  FindTBBHelper.cmake : Project_Required_TBB_COMPONENTS variable is already set [${Project_Required_TBB_COMPONENTS}]")
    endif()
endif()

find_package(TBB COMPONENTS ${Project_Required_TBB_COMPONENTS})

if(TBB_FOUND)
    foreach(_TBB_Comp ${Project_Required_TBB_COMPONENTS})
        if(NOT WIN32)
            makeTargetNoSymlink("TBB" "${_TBB_Comp}" "")
        endif()
        copyImportedSharedLibrary("TBB" ${_TBB_Comp} ".")
    endforeach()
endif()


function(print_tbb_info)
    foreach(_TBB_Comp ${Project_Required_TBB_COMPONENTS})
        echo_target(TBB::${_TBB_Comp} ".")
    endforeach()
endfunction()
