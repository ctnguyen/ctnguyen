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

macro(linkBoostUnitTest targetName)
    if(NOT TARGET ${targetName})
        message(FATAL_ERROR "[${targetName}] is not a TARGET")
    endif()

    set_property(TARGET ${targetName} PROPERTY FOLDER "Test/unit/cpp")
    add_test( NAME ${targetName} COMMAND $<TARGET_FILE:${targetName}>)
    target_link_libraries(${targetName} Boost::unit_test_framework)

    if(UNIX)
        target_link_libraries(${targetName} ${CMAKE_DL_LIBS})
    endif()
endmacro()

###############
add_executable(test_boost_date_time test_boost_date_time.cpp)
target_link_libraries(test_boost_date_time Boost::date_time Boost::regex)
linkBoostUnitTest(test_boost_date_time)

###############
add_executable(test_boost_dll test_boost_dll.cpp)
target_link_libraries(test_boost_dll Boost::filesystem)
linkBoostUnitTest(test_boost_dll)

###############
add_executable(test_boost_factory test_boost_factory.cpp)
linkBoostUnitTest(test_boost_factory)

###############
add_executable(test_boost_format test_boost_format.cpp)
linkBoostUnitTest(test_boost_format)

###############
add_executable(test_boost_log test_boost_log.cpp)
target_link_libraries(test_boost_log Boost::log Boost::log_setup)
linkBoostUnitTest(test_boost_log)

###############
add_executable(test_boost_random test_boost_random.cpp)
target_link_libraries(test_boost_random Boost::random)
linkBoostUnitTest(test_boost_random)

###############
add_executable(test_boost_spirit test_boost_spirit.cpp)
linkBoostUnitTest(test_boost_spirit)

###############
add_executable(test_cpp_codec test_cpp_codec.cpp)
target_link_libraries(test_cpp_codec Boost::random)
linkBoostUnitTest(test_cpp_codec)

###############
add_executable(test_cryptopp test_cryptopp.cpp)
# Link to CRYPTOPP
## http://floooh.github.io/2016/01/12/cmake-dependency-juggling.html
target_include_directories(test_cryptopp PUBLIC ${CRYPTOPP_INCLUDE_DIR})
target_link_libraries(test_cryptopp ${CRYPTOPP_LIBRARIES})
linkBoostUnitTest(test_cryptopp)

###############
add_executable(test_newcpp test_newcpp.cpp)
linkBoostUnitTest(test_newcpp)

###############
add_executable(test_RapidJSON test_RapidJSON.cpp)
target_include_directories(test_RapidJSON PUBLIC ${RAPIDJSON_ROOT}/include)
linkBoostUnitTest(test_RapidJSON)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)## DO NOT add this file to repository
    include(${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake)
    message(STATUS "Postconfig Local File [${CMAKE_CURRENT_SOURCE_DIR}/Local-PostConfig.cmake] has been included")
endif()
