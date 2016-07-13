#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

add_definitions(-DBOOST_ALL_DYN_LINK) # Use boost dll versions, lib without lib prefix
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(test_Boost_Variant test_Boost_Variant.cpp)
target_link_libraries(test_Boost_Variant ${Boost_LIBRARIES})
add_test(test_Boost_Variant test_Boost_Variant)