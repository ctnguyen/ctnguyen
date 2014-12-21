######## CMakeList.txt test for boost mpi  #######
cmake_minimum_required(VERSION 2.8.12)

#set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

project(cppx11 C CXX)

if(NOT WIN32)
set(CMAKE_CXX_FLAGS "-pthread")
endif()

### Setting for c++11x
#
# http://stackoverflow.com/questions/18358389/eclipse-indexer-proper-c11-syntax-highlighting-when-generating-projects-with-c
#set(CMAKE_ECLIPSE_VERSION "4.2")
#set(CMAKE_CXX_COMPILER_ARG1 "-std=c++11")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

#explicitly linking by giving the mpi include path and mpi libraries and using normal compiler
if(WIN32)
set_target_properties(cppx11 PROPERTIES LINK_FLAGS /LIBPATH:"${Boost_LIBRARY_DIRS}")
endif(WIN32)


add_executable(cppx11 main.cpp)
target_link_libraries(cppx11 ${Boost_LIBRARIES})  

add_executable(move_example move_example.cpp)

add_executable(multi_thread multi_thread/multi_thread.cpp)
add_executable(race_condition_ex multi_thread/race_condition_ex.cpp)
