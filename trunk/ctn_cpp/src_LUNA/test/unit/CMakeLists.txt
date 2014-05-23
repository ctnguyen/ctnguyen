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
#################################################
add_executable(test_Interpolation "test_Interpolation.cpp")
target_link_libraries(test_Interpolation LMM_numeric)
add_test(test_Interpolation ${CMAKE_CURRENT_BINARY_DIR}/test_Interpolation "--log_level=message")

add_executable(test_NumericalMethods "test_NumericalMethods.cpp")
target_link_libraries(test_NumericalMethods LMM_numeric)
add_test(test_NumericalMethods ${CMAKE_CURRENT_BINARY_DIR}/test_NumericalMethods "--log_level=message")