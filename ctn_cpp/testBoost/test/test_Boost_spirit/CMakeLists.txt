add_definitions(-DBOOST_ALL_DYN_LINK) # Use boost dll versions, lib without lib prefix

add_executable(test_Boost_Spirit test_Boost_Spirit.cpp)
target_compile_definitions(test_Boost_Spirit PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
target_link_libraries(test_Boost_Spirit Boost::unit_test_framework)
add_test(NAME test_Boost_Spirit COMMAND $<TARGET_FILE:test_Boost_Spirit>)
set_property(TARGET test_Boost_Spirit PROPERTY FOLDER "test/Boost_Spirit")

add_executable(test_Boost_Spirit_examples test_Boost_Spirit_examples.cpp)
target_compile_definitions(test_Boost_Spirit_examples PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
target_link_libraries(test_Boost_Spirit_examples Boost::unit_test_framework)
add_test(NAME test_Boost_Spirit_examples COMMAND $<TARGET_FILE:test_Boost_Spirit_examples>)
set_property(TARGET test_Boost_Spirit_examples PROPERTY FOLDER "test/Boost_Spirit")

add_executable(test_Boost_Spirit_AQL test_Boost_Spirit_AQL.cpp)
target_compile_definitions(test_Boost_Spirit_AQL PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
target_link_libraries(test_Boost_Spirit_AQL Boost::unit_test_framework)
add_test(NAME test_Boost_Spirit_AQL COMMAND $<TARGET_FILE:test_Boost_Spirit_AQL>)
set_property(TARGET test_Boost_Spirit_AQL PROPERTY FOLDER "test/Boost_Spirit")