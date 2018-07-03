############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################

## Include guard
if(MachineInfoSetting_Include)
  return()
endif()
set(MachineInfoSetting_Include TRUE)


#### INVESTIGATE AND SET VARIABLE TO HOLD 
#### SYSTEM_OS          win/linux/mac
#### SYSTEM_BUILD_ARCHI x64/x86

### LOW LEVEL INVESTIGATE OF SYSTEMTEM
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SYSTEM_X64 ON)
    set(SYSTEM_BUILD_ARCHI x64)
else()
    set(SYSTEM_X86 ON)
    set(SYSTEM_BUILD_ARCHI x86)
endif()
if(WIN32) #Windows
    set(SYSTEM_OS windows)
else()    # UNIX
    if(APPLE)
        set(SYSTEM_OS mac)
    else()
        set(SYSTEM_OS linux)
    endif()
endif()