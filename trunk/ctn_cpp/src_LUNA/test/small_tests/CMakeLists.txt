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

add_executable(test_LMMTenorStructure "Test_LMMTenorStructure.cpp")
target_link_libraries(test_LMMTenorStructure LMM_ModelMCLMM)
add_test(test_LMMTenorStructure ${CMAKE_CURRENT_BINARY_DIR}/test_LMMTenorStructure "--log_level=message")

add_executable(test_VolatilityFunction "Test_VolatilityFunction.cpp")
target_link_libraries(test_VolatilityFunction LMM_ModelMCLMM)
add_test(test_VolatilityFunction ${CMAKE_CURRENT_BINARY_DIR}/test_VolatilityFunction "--log_level=message")



