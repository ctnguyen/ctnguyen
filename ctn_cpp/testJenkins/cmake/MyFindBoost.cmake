############################################################### #
#  Date             10/02/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#################################################################

## Before building boost, need to install bzip2-devel, python-devel
## build boost 
## Build command on linux
## sudo ./b2 --with=all link=shared,static runtime-link=shared
##  Build command on Windows (same?)
##
if(CUSTOM_CTNGUYEN_BOOST_ROOT)
    set(BOOST_ROOT ${CUSTOM_CTNGUYEN_BOOST_ROOT})
elseif(DEFINED ENV{BOOST_ROOT})
    set(BOOST_ROOT $ENV{BOOST_ROOT})
elseif(CTNGUYEN_FRAMEWORKS_BOOST_ROOT)
    set(BOOST_ROOT ${CTNGUYEN_FRAMEWORKS_BOOST_ROOT})
endif()

find_package(Threads) ## find threads first might fix a warning when looking for boost thread

message("  -- CTNGUYEN try to find Boost in [${BOOST_ROOT}]")
## http://stackoverflow.com/questions/6646405/how-do-you-add-boost-libraries-in-cmakelists-txt
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

## dont forget to add 
# target_compile_definitions(yourtarget PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
# target_link_libraries(${projNAME} Boost::your_boost_component)

find_package(Boost 1.61. COMPONENTS date_time thread chrono filesystem system REQUIRED)

message("")