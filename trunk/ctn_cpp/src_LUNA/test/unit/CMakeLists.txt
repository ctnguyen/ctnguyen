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

#add_executable(unitTest_helper_QMcGenerator "test_helper_QMcGenerator.cpp")
#target_link_libraries(unitTest_helper_QMcGenerator LMM_helper)
#add_test(unitTest_helper_QMcGenerator ${CMAKE_CURRENT_BINARY_DIR}/unitTest_helper_QMcGenerator "--log_level=message")

add_executable(unitTest_helper_Tensor "test_helper_Tensor.cpp")
target_link_libraries(unitTest_helper_Tensor LMM_helper)
add_test(unitTest_helper_Tensor ${CMAKE_CURRENT_BINARY_DIR}/unitTest_helper_Tensor "--log_level=message")

add_executable(unitTest_helper_Tenor "test_Tenor.cpp")
target_link_libraries(unitTest_helper_Tenor LMM_helper)
add_test(unitTest_helper_Tenor ${CMAKE_CURRENT_BINARY_DIR}/unitTest_helper_Tenor "--log_level=message")

add_executable(unitTest_helper_LMMTenorStructure "test_helper_LMMTenorStructure.cpp")
target_link_libraries(unitTest_helper_LMMTenorStructure LMM_helper)
add_test(unitTest_helper_LMMTenorStructure ${CMAKE_CURRENT_BINARY_DIR}/unitTest_helper_LMMTenorStructure "--log_level=message")

add_executable(unitTest_instrument_VanillaSwap "test_instrument_VanillaSwap.cpp")
target_link_libraries(unitTest_instrument_VanillaSwap LMM_instrument)
add_test(unitTest_instrument_VanillaSwap ${CMAKE_CURRENT_BINARY_DIR}/unitTest_instrument_VanillaSwap "--log_level=message")

#add_executable(unitTest_ModelMCLMM_PCA "test_ModelMCLMM_PCA.cpp")
#target_link_libraries(unitTest_ModelMCLMM_PCA LMM_ModelMCLMM ${QuantLib_LIBRARY})
#add_test(unitTest_ModelMCLMM_PCA ${CMAKE_CURRENT_BINARY_DIR}/unitTest_ModelMCLMM_PCA "--log_level=message")

add_executable(unitTest_ModelMCLMM_RobonatoAngle "test_ModelMCLMM_RobonatoAngle.cpp")
target_link_libraries(unitTest_ModelMCLMM_RobonatoAngle LMM_ModelMCLMM ${QuantLib_LIBRARY})
add_test(unitTest_ModelMCLMM_RobonatoAngle ${CMAKE_CURRENT_BINARY_DIR}/unitTest_ModelMCLMM_RobonatoAngle "--log_level=message")

add_executable(unitTest_ModelMCLMM_Correlation "test_ModelMCLMM_Correlation.cpp")
target_link_libraries(unitTest_ModelMCLMM_Correlation LMM_ModelMCLMM ${QuantLib_LIBRARY})
add_test(unitTest_ModelMCLMM_Correlation ${CMAKE_CURRENT_BINARY_DIR}/unitTest_ModelMCLMM_Correlation "--log_level=message")

add_executable(unitTest_pricer_LmmApproxVanillaSwaptionPricer "test_pricer_LmmApproxVanillaSwaptionPricer.cpp")
target_link_libraries(unitTest_pricer_LmmApproxVanillaSwaptionPricer LMM_pricer ${QuantLib_LIBRARY})
add_test(unitTest_pricer_LmmApproxVanillaSwaptionPricer ${CMAKE_CURRENT_BINARY_DIR}/unitTest_pricer_LmmApproxVanillaSwaptionPricer "--log_level=message")

add_executable(unittest_calibration_SwaptionApproxCostFunction "test_calibration_SwaptionApproxCostFunction.cpp")
target_link_libraries(unittest_calibration_SwaptionApproxCostFunction LMM_calibration ${QuantLib_LIBRARY})
add_test(unittest_calibration_SwaptionApproxCostFunction ${CMAKE_CURRENT_BINARY_DIR}/unittest_calibration_SwaptionApproxCostFunction "--log_level=message")

