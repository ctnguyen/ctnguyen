######## CMakeList.txt test for boost mpi  #######
cmake_minimum_required(VERSION 2.8)

project(cppx11)

find_package(Boost)

#explicitly linking by giving the mpi include path and mpi libraries and using normal compiler
if(UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif(UNIX)

if(WIN32)
set_target_properties(cppx11 PROPERTIES LINK_FLAGS /LIBPATH:"${Boost_LIBRARY_DIRS}")
endif(WIN32)

include_directories(${Boost_INCLUDE_DIRS})



add_executable(cppx11 main.cpp)
target_link_libraries(cppx11 ${Boost_LIBRARIES})  

add_executable(multi_thread multi_thread/multi_thread.cpp)