#################################################################
#  Date             14/08/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                             
#################################################################
## Include guard
if(SetBuildVersion_Include)
  return()
endif()
set(SetBuildVersion_Include TRUE)

set(CMAKEDEBUG_SetBuildVersion ON)# Set to ON if want to debug
#### DEFINE BUILD VERSION VARIABLES
#### Based on the defined 
####    ${CTN_GIT_BRANCH}]
####    ${CTN_GIT_COMMIT_HASH}
####    ${CTN_BUILD_DATETIME_UTC}

if(NOT CTN_VERSION_MAJOR)
    set(CTN_VERSION_MAJOR 3)
endif()

if(NOT CTN_VERSION_MINOR)
    set(CTN_VERSION_MINOR 2)
endif()

if(NOT CTN_VERSION_PATCH)
    set(CTN_VERSION_PATCH 7)
endif()

if(NOT CTN_VERSION_MAINTENANCE)
    set(CTN_VERSION_MAINTENANCE 7)
endif()

set(CTN_GIT_BRANCH "${CTN_GIT_BRANCH}")
set(CTN_GIT_COMMIT_HASH "${CTN_GIT_COMMIT_HASH}")
set(CTN_BUILD_DATETIME_UTC "${CTN_BUILD_DATETIME_UTC}")