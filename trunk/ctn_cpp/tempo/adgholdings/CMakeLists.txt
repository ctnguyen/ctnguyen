#CMAKE INITIALIZATION
cmake_minimum_required(VERSION 3.0)

project(adgholdings) 

set(CTN_BUILD_TEST true)
#set(CTN_BUILD_TEST false)

# Do not use Debug/Release folder on Windows.
if(WIN32)
	set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "" )
	set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "" )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "" )
endif()

if(CTN_BUILD_TEST)
	add_definitions(-DCTN_BUILD_TEST)
endif()

set(CTN_SOURCES Question1.h Question2.h Question3.h Question4.h)# ) 

if(WIN32)
	add_executable(prog ${CTN_SOURCES} "main.cpp")	
else()
	add_executable(prog.exe ${CTN_SOURCES} "main.cpp")
endif()

# Build test 
if(CTN_BUILD_TEST)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

add_executable(unittest_Q1 "unittest_Q1.cpp")
add_test(unittest_Q1 unittest_Q1 "--log_level=message")

add_executable(unittest_Q2 "unittest_Q2.cpp")
add_test(unittest_Q2 unittest_Q2 "--log_level=message")

add_executable(unittest_Q3 "unittest_Q3.cpp")
add_test(unittest_Q3 unittest_Q3 "--log_level=message")

add_executable(unittest_Q4 "unittest_Q4.cpp")
add_test(unittest_Q4 unittest_Q4 "--log_level=message")


endif()
