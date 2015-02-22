add_executable(test_DataStream "test_DataStream.cpp")
target_link_libraries(test_DataStream ctn_lib)
add_test(test_DataStream test_DataStream "--log_level=message")

add_executable(test_Selection "test_Selection.cpp")
target_link_libraries(test_Selection ctn_lib)
add_test(test_Selection test_Selection "--log_level=message")

file(COPY "${CMAKE_SOURCE_DIR}/test/sample.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/")
if(MSVC)
	file(COPY "${CMAKE_SOURCE_DIR}/test/sample.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/Debug/")
endif()

file(COPY "${CMAKE_SOURCE_DIR}/test/test_SelectionSample3.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/")
if(MSVC)
	file(COPY "${CMAKE_SOURCE_DIR}/test/test_SelectionSample3.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/Debug/")
endif()