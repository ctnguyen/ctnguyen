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

add_executable(test_ublasBoostMatrix "Test_ublasBoostMatrix.cpp")
add_test(test_ublasBoostMatrix ${CMAKE_CURRENT_BINARY_DIR}/test_ublasBoostMatrix "--log_level=message")
