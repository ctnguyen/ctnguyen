cmake_minimum_required(VERSION 2.8)

if(UNIX)
set(CMAKE_GENERATOR "Unix Makefiles") 
set(CMAKE_EXTRA_GENERATOR "Eclipse CDT4" CACHE STRING  "Gerator for Eclipse CDT" FORCE)
endif()

project(test_WINZAF)

add_executable(
	test_winzaf
	conio.h
	WINZAF.CPP
)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
if(CURSES_FOUND)
message("------------------------- found library curse")
message("------------------------ CURSES_INCLUDE_DIR  found ${CURSES_INCLUDE_DIR}")
message("------------------------ CURSES_LIBRARIES  found ${CURSES_LIBRARIES}")
endif()

include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(test_winzaf ${CURSES_LIBRARIES})





#  CURSES_FOUND - system has Curses
#  CURSES_INCLUDE_DIR - the Curses include directory
#  CURSES_LIBRARIES - The libraries needed to use Curses
#  CURSES_HAVE_CURSES_H - true if curses.h is available
#  CURSES_HAVE_NCURSES_H - true if ncurses.h is available
#  CURSES_HAVE_NCURSES_NCURSES_H - true if ncurses/ncurses.h is available
#  CURSES_HAVE_NCURSES_CURSES_H - true if ncurses/curses.h is available
#  CURSES_LIBRARY - set for backwards compatibility with 2.4 CMake
#
