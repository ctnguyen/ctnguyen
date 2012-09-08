cmake_minimum_required(VERSION 2.8)

if(UNIX)
set(CMAKE_GENERATOR "Unix Makefiles") 
set(CMAKE_EXTRA_GENERATOR "Eclipse CDT4" CACHE STRING  "Gerator for Eclipse CDT" FORCE)
endif()

project(test_WINZAF)

add_executable(
	test_winzaf
	WINZAF.CPP
)
