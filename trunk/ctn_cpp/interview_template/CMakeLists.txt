#CMAKE INITIALIZATION
cmake_minimum_required(VERSION 3.0)

project(Interview) 

set(CTN_BUILD_TEST true)

# Do not use Debug/Release folder on Windows.
if(WIN32)
	set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "" )
	set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "" )
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "" )
endif()

add_library(ctn_lib MyClass.h MyClass.cpp)

add_executable(prog "main.cpp")
target_link_libraries(prog ctn_lib)

# Build test 
if(CTN_BUILD_TEST)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

add_executable(unittest_MyClass "unittest_MyClass.cpp")
target_link_libraries(unittest_MyClass ctn_lib)
add_test(unittest_MyClass unittest_MyClass "--log_level=message")

endif()