#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.3)

project(ancoa_cmake_test) 

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(Proj1)
add_subdirectory(Proj2)
add_subdirectory(ProjA)
add_subdirectory(ProjB)

add_subdirectory(Prog1A)
add_subdirectory(Prog2B)

# if found boost test framework
#add_subdirectory(Test)