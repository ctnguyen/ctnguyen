#################################################
#                                               #
#   C++ PROGRAMMING                             #
#   MASTER LAURE ELIE 2013-2014                 #
#   Student Chi Thanh NGUYEN                    # 
#                                               #
#   chithanhnguyen.math@gmail.com               #
#################################################

add_library(lib_tp1 lib_tp1.cpp)

add_library(lib_tp2 lib_tp2.cpp)
target_link_libraries(lib_tp2 lib_tp1)