######## CMakeList.txt test for boost mpi  #######
cmake_minimum_required(VERSION 2.8)

project(cppx11)

find_package(Boost)

### Setting for c++11x
#
# http://stackoverflow.com/questions/18358389/eclipse-indexer-proper-c11-syntax-highlighting-when-generating-projects-with-c
#set(CMAKE_ECLIPSE_VERSION "4.2")
#set(CMAKE_CXX_COMPILER_ARG1 "-std=c++11")

#explicitly linking by giving the mpi include path and mpi libraries and using normal compiler
if(WIN32)
set_target_properties(cppx11 PROPERTIES LINK_FLAGS /LIBPATH:"${Boost_LIBRARY_DIRS}")
endif(WIN32)

include_directories(${Boost_INCLUDE_DIRS})


add_executable(cppx11 main.cpp)
target_link_libraries(cppx11 ${Boost_LIBRARIES})  

add_executable(multi_thread multi_thread/multi_thread.cpp)