############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake)
    message(STATUS "Preconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PreConfig.cmake] has been included")
endif()

if(BUILD_BOOST_EXAMPLE) ## Customize build boost example
    include(${CMAKE_CURRENT_SOURCE_DIR}/BuildBoostExampleHelper.cmake)
endif()

## todo : 
#add_subdirectory(test_websocket)
#add_subdirectory(test_rest)

if(TgBot_FOUND)
    add_subdirectory(telegram_bot)
endif()

#if(PYTHONLIBS_FOUND) ## Issue here : boost by default build with python2, need to rebuild boost with python3. Because python3 is installed
#    add_subdirectory(test_boost_python)
#endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)
    message(STATUS "Postconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake] has been included")
endif()