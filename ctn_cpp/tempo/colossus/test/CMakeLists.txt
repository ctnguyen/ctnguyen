include_directories(${CMAKE_SOURCE_DIR})

add_executable(test_DataStream "test_DataStream.cpp")
target_link_libraries(test_DataStream ctn_lib)
add_test(test_DataStream test_DataStream "--log_level=message")

add_executable(test_Selection "test_Selection.cpp")
target_link_libraries(test_Selection ctn_lib)
add_test(test_Selection test_Selection "--log_level=message")

add_executable(test_STL_Container "test_STL_Container.cpp")
target_link_libraries(test_STL_Container ctn_lib)
add_test(test_STL_Container test_STL_Container "--log_level=message")

add_executable(test_Median "test_Median.cpp")
target_link_libraries(test_Median ctn_lib)
add_test(test_Median test_Median "--log_level=message")

add_executable(ctn_time_measure "time_measure.cpp")
target_link_libraries(ctn_time_measure ctn_lib)

file(COPY "${CMAKE_SOURCE_DIR}/test/sample.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/")
if(MSVC)
	file(COPY "${CMAKE_SOURCE_DIR}/test/sample.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/Debug/")
endif()

file(COPY "${CMAKE_SOURCE_DIR}/test/test_SelectionSample3.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/")
if(MSVC)
	file(COPY "${CMAKE_SOURCE_DIR}/test/test_SelectionSample3.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/Debug/")
endif()

file(COPY "${CMAKE_SOURCE_DIR}/test/sample_data_1000.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/")
file(COPY "${CMAKE_SOURCE_DIR}/test/sample_data_1000.txt" DESTINATION "${CMAKE_BINARY_DIR}/")
if(MSVC)
	file(COPY "${CMAKE_SOURCE_DIR}/test/sample_data_1000.txt" DESTINATION "${CMAKE_BINARY_DIR}/test/Debug/")
	file(COPY "${CMAKE_SOURCE_DIR}/test/sample_data_1000.txt" DESTINATION "${CMAKE_BINARY_DIR}/Debug/")
endif()