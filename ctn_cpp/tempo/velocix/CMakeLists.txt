#CMAKE INITIALIZATION
cmake_minimum_required(VERSION 3.0)

project(velocix) 

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

add_library(ctnlib
	Helper.h
	NodeWord.h
	TextProcess.h
	Word.h
	NodeWord.cpp
	TextProcess.cpp
	Word.cpp)

if(WIN32)
	add_executable(prog "main.cpp")
	target_link_libraries(prog ctnlib)
else()
	add_executable(prog.exe "main.cpp")
	target_link_libraries(prog.exe ctnlib)
endif()

file(COPY "${CMAKE_SOURCE_DIR}/referece_text.txt" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/sample_text.txt" DESTINATION "${CMAKE_BINARY_DIR}")

# Build test 
if(CTN_BUILD_TEST)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

add_executable(unittest_Helper "unittest_Helper.cpp")
target_link_libraries(unittest_Helper ctnlib)
add_test(unittest_Helper unittest_Helper "--log_level=message")

add_executable(unittest_NodeWord "unittest_NodeWord.cpp")
target_link_libraries(unittest_NodeWord ctnlib)
add_test(unittest_NodeWord unittest_NodeWord "--log_level=message")

add_executable(unittest_TextProcess "unittest_TextProcess.cpp")
target_link_libraries(unittest_TextProcess ctnlib)
add_test(unittest_TextProcess unittest_TextProcess "--log_level=message")

add_executable(unittest_Word "unittest_Word.cpp")
target_link_libraries(unittest_Word ctnlib)
add_test(unittest_Word unittest_Word "--log_level=message")


endif()
