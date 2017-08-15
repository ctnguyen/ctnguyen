#################################################################
#  Date             14/08/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                             
#################################################################
## Include guard
if(MachineInfoSetting_Include)
  return()
endif()
set(MachineInfoSetting_Include TRUE)

#### INVESTIGATE AND SET VARIABLE TO HOLD 
#### CTN_OS          win/linux/mac
#### CTN_BUILD_ARCHI x64/x86


### LOW LEVEL INVESTIGATE OF SYSTEM
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CTN_X64 ON)
    set(CTN_BUILD_ARCHI x64)
else()
    set(CTN_X86 ON)
    set(CTN_BUILD_ARCHI x86)
endif()
if(WIN32)
    set(CTN_OS win)
else()
    set(CTN_OS linux)
endif()