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
add_executable(unitTest_BoostUblasMatrix "test_BoostUblasMatrix.cpp")
add_test(unitTest_BoostUblasMatrix ${CMAKE_CURRENT_BINARY_DIR}/unitTest_BoostUblasMatrix "--log_level=message")

add_executable(unitTest_QuantLibIntegrationMethod "test_QuantLibIntegrationMethod.cpp")
target_link_libraries(unitTest_QuantLibIntegrationMethod ${QuantLib_LIBRARY})
add_test(unitTest_QuantLibIntegrationMethod ${CMAKE_CURRENT_BINARY_DIR}/unitTest_QuantLibIntegrationMethod "--log_level=message")

add_executable(unitTest_numeric_Interpolation "test_numeric_Interpolation.cpp")
target_link_libraries(unitTest_numeric_Interpolation LMM_numeric)
add_test(unitTest_numeric_Interpolation ${CMAKE_CURRENT_BINARY_DIR}/unitTest_numeric_Interpolation "--log_level=message")

add_executable(unitTest_numeric_NumericalMethods "test_numeric_NumericalMethods.cpp")
target_link_libraries(unitTest_numeric_NumericalMethods LMM_numeric)
add_test(unitTest_numeric_NumericalMethods ${CMAKE_CURRENT_BINARY_DIR}/unitTest_numeric_NumericalMethods "--log_level=message")

add_executable(unitTest_helper_MarketInfoCollector "test_helper_MarketInfoCollector.cpp")
target_link_libraries(unitTest_helper_MarketInfoCollector LMM_helper)
add_test(unitTest_helper_MarketInfoCollector ${CMAKE_CURRENT_BINARY_DIR}/unitTest_helper_MarketInfoCollector "--log_level=message")

add_executable(unitTest_instrument_Tenor "test_Tenor.cpp")
target_link_libraries(unitTest_instrument_Tenor LMM_instrument)
add_test(unitTest_instrument_Tenor ${CMAKE_CURRENT_BINARY_DIR}/unitTest_instrument_Tenor "--log_level=message")

add_executable(unittest_SwaptionApproxCostFunction "test_SwaptionApproxCostFunction.cpp")
target_link_libraries(unittest_SwaptionApproxCostFunction LMM_pricer ${QuantLib_LIBRARY})
add_test(unittest_SwaptionApproxCostFunction ${CMAKE_CURRENT_BINARY_DIR}/unittest_SwaptionApproxCostFunction "--log_level=message")

