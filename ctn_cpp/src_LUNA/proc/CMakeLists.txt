add_executable(procLMM "Main.cpp")

target_link_libraries(procLMM LMM_testlib LMM_ModelMCLMM LMM_instrument LMM_numeric LMM_helper ${QuantLib_LIBRARY})
