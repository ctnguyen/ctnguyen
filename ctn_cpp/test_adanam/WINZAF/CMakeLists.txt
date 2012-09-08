cmake_minimum_required(VERSION 2.8)

if(UNIX)
set(CMAKE_GENERATOR "Unix Makefiles") 
set(CMAKE_EXTRA_GENERATOR "Eclipse CDT4" CACHE STRING  "Gerator for Eclipse CDT" FORCE)
endif()

project(test_WINZAF)

configure_file("${CMAKE_SOURCE_DIR}/samples.txt" "${CMAKE_CURRENT_BINARY_DIR}/source.txt" @ONLY)

add_executable(
	test_winzaf
	WINZAF.CPP
)

add_executable(
    sample_binair
    sample_binair.cpp
)