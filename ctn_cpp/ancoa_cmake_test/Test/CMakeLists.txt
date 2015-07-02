enable_testing()

set(unitTestList
    test_Proj1.cpp
    test_Proj2.cpp
    test_ProjA.cpp
    test_ProjB.cpp
)

foreach(unitTestItem ${unitTestList})
    message(STATUS "ctn unit tests ${unitTestItem}")
endforeach()

set(LongTimeTestList
    test_LongTime1.cpp
    test_LongTime2.cpp
)

foreach(longTestItem ${LongTimeTestList})
    message(STATUS "ctn LongTime tests ${longTestItem}")
endforeach()

#add_definitions(-DBOOST_TEST_DYN_LINK) # use when linking with precompiled boost test frameworks

add_executable(test_Proj1 "test_Proj1.cpp")
add_test(test_Proj1 test_Proj1 "--log_level=message")
target_link_libraries(test_Proj1 Proj1)

add_executable(test_Proj2 "test_Proj2.cpp")
add_test(test_Proj2 test_Proj2 "--log_level=message")
target_link_libraries(test_Proj2 Proj2)

add_executable(test_ProjA "test_ProjA.cpp")
add_test(test_ProjA test_ProjA "--log_level=message")
target_link_libraries(test_ProjA ProjA)

add_executable(test_ProjB "test_ProjB.cpp")
add_test(test_ProjB test_ProjB "--log_level=message")
target_link_libraries(test_ProjB ProjB)

add_executable(test_LongTime1 "test_LongTime1.cpp")
add_test(test_LongTime1 test_LongTime1 "--log_level=message")
target_link_libraries(test_LongTime1 Proj1 ProjA)

add_executable(test_LongTime2 "test_LongTime2.cpp")
add_test(test_LongTime2 test_LongTime2 "--log_level=message")
target_link_libraries(test_LongTime2 Proj2 ProjB)