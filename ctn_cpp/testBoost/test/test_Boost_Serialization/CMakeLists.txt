#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

# cmake path/to/source/folder/ -G"Visual Studio 12 2013 Win64"
# cmake path/to/source/folder/ -G"Eclipse CDT4 - Unix Makefiles"
# cmake path/to/source/folder/ -G"CodeBlocks – Unix Makefiles"

add_definitions(-DBOOST_ALL_DYN_LINK) # Use boost dll versions, lib without lib prefix
find_package(Boost REQUIRED COMPONENTS serialization iostreams unit_test_framework)
message("                       Boost_INCLUDE_DIR [${Boost_INCLUDE_DIR}]")
message("                      Boost_INCLUDE_DIRS [${Boost_INCLUDE_DIRS}]")
message("                         Boost_LIBRARIES [${Boost_LIBRARIES}]")
message("       Boost_UNIT_TEST_FRAMEWORK_LIBRARY [${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}]")
include_directories(${Boost_INCLUDE_DIRS})

add_executable(test_Boost_SerializationAllNativeType test_Boost_SerializationAllNativeType.cpp)
target_link_libraries(test_Boost_SerializationAllNativeType ${Boost_LIBRARIES})
add_test(test_Boost_SerializationAllNativeType test_Boost_SerializationAllNativeType)

add_executable(test_Boost_Serialization_TypeTracking test_Boost_Serialization_TypeTracking.cpp)
target_link_libraries(test_Boost_Serialization_TypeTracking ${Boost_LIBRARIES})
add_test(test_Boost_Serialization_TypeTracking test_Boost_Serialization_TypeTracking)

#add_test(NAME test_Boost_SerializationAllNativeType COMMAND "test_Boost_SerializationAllNativeType --log_level=message")

#add_executable(test_Boost_Serialization test_Boost_Serialization.cpp)
#target_link_libraries(test_Boost_Serialization ${Boost_LIBRARIES})

#add_executable(test_Boost_BinarySerialization test_Boost_BinarySerialization.cpp)
#target_link_libraries(test_Boost_BinarySerialization ${Boost_LIBRARIES})

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#add_subdirectory(demo_trivial_archive)
#add_subdirectory(demo_fast_archive)
#add_subdirectory(demo_portable_archive)