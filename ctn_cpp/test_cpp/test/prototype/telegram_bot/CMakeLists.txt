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


add_executable (test_telegram_bot test_telegram_bot.cpp)
## Linking with boost, telegram bot
target_include_directories(test_telegram_bot PUBLIC ${TgBot_INCLUDE_DIR})
target_link_libraries(test_telegram_bot ${TgBot_LIBRARIES} Boost::system Boost::date_time Boost::program_options OpenSSL::SSL ${CMAKE_THREAD_LIBS_INIT})
## Set folder structure in IDE
set_property(TARGET test_telegram_bot PROPERTY FOLDER "Test/prototype")

InstallProgram(test_telegram_bot)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)
    message(STATUS "Postconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake] has been included")
endif()
