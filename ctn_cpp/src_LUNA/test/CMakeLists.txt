#################################################
#   chithanhnguyen.math@gmail.com               #
#                                               #
#   Lunalogic intership project 2014            #
#   LIBOR Market Model                          #
#   Technologies:                               #
#   - cmake                                     #
#   - boost                                     #
#   - QuantLib                                  #
#                                               #
#   14.Mai.2014                                 #
#################################################

add_subdirectory(testlib)
add_subdirectory(small_tests)

add_executable(test_testlib "Test_TestLib.cpp")
target_link_libraries(test_testlib LMM_testlib LMM_ModelMCLMM LMM_instrument LMM_numeric LMM_helper ${QuantLib_LIBRARY})
#add_test(oldtests ${CMAKE_CURRENT_BINARY_DIR}/test_testlib "--log_level=message")
