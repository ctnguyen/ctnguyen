
add_executable(test_DataStream "test_DataStream.cpp")
target_link_libraries(test_DataStream ctn_lib)
add_test(test_DataStream test_DataStream "--log_level=message")

