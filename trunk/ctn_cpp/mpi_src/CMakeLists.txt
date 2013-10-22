######## CMakeList.txt test for boost mpi  #######
cmake_minimum_required(VERSION 2.8)

project(mpi_test)

add_executable(mpi_test main.cpp)

find_package(MPI REQUIRED)
find_package(Boost COMPONENTS mpi serialization REQUIRED)

#explicitly linking by giving the mpi include path and mpi libraries and using normal compiler
if(WIN32)
set_target_properties(mpi_test PROPERTIES LINK_FLAGS /LIBPATH:"${Boost_LIBRARY_DIRS}")
endif(WIN32)
include_directories(${MPI_INCLUDE_PATH} ${Boost_INCLUDE_DIRS})
target_link_libraries(mpi_test ${MPI_LIBRARIES} ${Boost_LIBRARIES})  
