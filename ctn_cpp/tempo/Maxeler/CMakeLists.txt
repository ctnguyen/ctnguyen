#CMAKE INITIALIZATION
cmake_minimum_required(VERSION 3.0)

project(Maxeler) 

#set(CTN_BUILD_TEST true)
set(CTN_BUILD_TEST false)

# Do not use Debug/Release folder on Windows.
if(WIN32)
	set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "" )
	set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "" )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "" )
endif()

if(CTN_BUILD_TEST)
	add_definitions(-DCTN_BUILD_TEST)
endif()

add_library(VMlib
			Operator.h
			Helper.h
			VMimage.h
			VMinterpreter.h
			Operator.cpp
			VMimage.cpp
			VMinterpreter.cpp)
if(WIN32)
	add_executable(task1 "task1.cpp")
	target_link_libraries(task1 VMlib)
	add_executable(task2 "task2.cpp")
	target_link_libraries(task2 VMlib)
else()
	add_executable(task1.exe "task1.cpp")
	target_link_libraries(task1.exe VMlib)
	add_executable(task2.exe "task2.cpp")
	target_link_libraries(task2.exe VMlib)
endif()

file(COPY "${CMAKE_SOURCE_DIR}/task1.bin" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/task2.bin" DESTINATION "${CMAKE_BINARY_DIR}")

# Build test 
if(CTN_BUILD_TEST)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

file(COPY "${CMAKE_SOURCE_DIR}/test_data" DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(unittest_BasicInstruction "unittest_BasicInstruction.cpp")
target_link_libraries(unittest_BasicInstruction VMlib)
add_test(unittest_BasicInstruction unittest_BasicInstruction "--log_level=message")

add_executable(unittest_VMimage "unittest_VMimage.cpp")
target_link_libraries(unittest_VMimage VMlib)
add_test(unittest_VMimage unittest_VMimage "--log_level=message")

add_executable(unittest_VMinterpreter "unittest_VMinterpreter.cpp")
target_link_libraries(unittest_VMinterpreter VMlib)
add_test(unittest_VMinterpreter unittest_VMinterpreter "--log_level=message")

file(COPY "${CMAKE_SOURCE_DIR}/test_script.sh" DESTINATION "${CMAKE_BINARY_DIR}")

endif()
