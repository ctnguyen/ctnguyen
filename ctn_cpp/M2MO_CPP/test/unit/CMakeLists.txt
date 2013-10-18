#################################################
#                                               #
#   C++ PROGRAMMING                             #
#   MASTER LAURE ELIE 2013-2014                 #
#   Student Chi Thanh NGUYEN                    # 
#                                               #
#   chithanhnguyen.math@gmail.com               #
#################################################

add_executable(test_lib_tp1 test_lib_tp1.cpp)
target_link_libraries(test_lib_tp1 lib_tp1)

add_test(test_lib_tp1 ${CMAKE_CURRENT_BINARY_DIR}/test_lib_tp1 "--log_level=message")


add_executable(test_lib_tp2 test_lib_tp2.cpp)
target_link_libraries(test_lib_tp2 lib_tp2)

add_test(test_lib_tp2 ${CMAKE_CURRENT_BINARY_DIR}/test_lib_tp2 "--log_level=message")



