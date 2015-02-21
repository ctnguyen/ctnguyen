
add_executable(test_DataStream "test_DataStream.cpp")
target_link_libraries(test_DataStream ctn_lib)
add_test(test_DataStream test_DataStream "--log_level=message")

if(MSVC)
	file(COPY "${CMAKE_SOURCE_DIR}/test/sample.txt" DESTINATION "${CMAKE_SOURCE_DIR}/test/Debug/sample.txt")
	#configure_file("${CMAKE_SOURCE_DIR}/test/sample.txt" "${CMAKE_BINARY_DIR}/test/Debug/sample.txt" @ONLY)
else()
	file(COPY "${CMAKE_SOURCE_DIR}/test/sample.txt" DESTINATION "${CMAKE_SOURCE_DIR}/test/sample.txt")
	#configure_file("${CMAKE_SOURCE_DIR}/test/sample.txt" "${CMAKE_BINARY_DIR}/test/sample.txt" @ONLY)
endif()