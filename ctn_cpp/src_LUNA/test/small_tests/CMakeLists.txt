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
add_executable(test_TenorTypePrototype "Test_TenorTypePrototype.cpp")
add_test(test_TenorTypePrototype ${CMAKE_CURRENT_BINARY_DIR}/test_TenorTypePrototype "--log_level=message")


add_executable(test_ublasBoostMatrix "Test_ublasBoostMatrix.cpp")
add_test(test_ublasBoostMatrix ${CMAKE_CURRENT_BINARY_DIR}/test_ublasBoostMatrix "--log_level=message")

add_executable(test_IntegrationMethod "Test_IntegrationMethod.cpp")
target_link_libraries(test_IntegrationMethod ${QuantLib_LIBRARY})
add_test(test_IntegrationMethod ${CMAKE_CURRENT_BINARY_DIR}/test_IntegrationMethod "--log_level=message")

add_executable(test_DerivatibleFunction "Test_DerivatibleFunction.cpp")
target_link_libraries(test_DerivatibleFunction LMM_helper)
add_test(test_DerivatibleFunction ${CMAKE_CURRENT_BINARY_DIR}/test_DerivatibleFunction "--log_level=message")

add_executable(test_BlackGreek "Test_BlackGreek.cpp")
target_link_libraries(test_BlackGreek LMM_helper LMM_numeric)
add_test(test_BlackGreek ${CMAKE_CURRENT_BINARY_DIR}/test_BlackGreek "--log_level=message")

add_executable(test_LMMTenorStructure "Test_LMMTenorStructure.cpp")
target_link_libraries(test_LMMTenorStructure LMM_ModelMCLMM)
add_test(test_LMMTenorStructure ${CMAKE_CURRENT_BINARY_DIR}/test_LMMTenorStructure "--log_level=message")

add_executable(test_VolatilityFunction "Test_VolatilityFunction.cpp")
target_link_libraries(test_VolatilityFunction LMM_ModelMCLMM)
add_test(test_VolatilityFunction ${CMAKE_CURRENT_BINARY_DIR}/test_VolatilityFunction "--log_level=message")

add_executable(test_McTerminalLmm "Test_McTerminalLmm.cpp")
target_link_libraries(test_McTerminalLmm LMM_ModelMCLMM LMM_helper)
add_test(test_McTerminalLmm ${CMAKE_CURRENT_BINARY_DIR}/test_McTerminalLmm "--log_level=message")

add_executable(test_VanillaSwapPricer "Test_VanillaSwapPricer.cpp")
target_link_libraries(test_VanillaSwapPricer LMM_pricer LMM_ModelMCLMM LMM_helper)
add_test(test_VanillaSwapPricer ${CMAKE_CURRENT_BINARY_DIR}/test_VanillaSwapPricer "--log_level=message")

add_executable(test_VanillaSwaptionPricer "Test_VanillaSwaptionPricer.cpp")
target_link_libraries(test_VanillaSwaptionPricer LMM_pricer LMM_ModelMCLMM LMM_helper)
add_test(test_VanillaSwaptionPricer ${CMAKE_CURRENT_BINARY_DIR}/test_VanillaSwaptionPricer "--log_level=message")