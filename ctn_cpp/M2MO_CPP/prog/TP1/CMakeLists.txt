#################################################
#                                               #
#   C++ PROGRAMMING                             #
#   MASTER LAURE ELIE 2013-2014                 #
#   Student Chi Thanh NGUYEN                    # 
#                                               #
#   chithanhnguyen.math@gmail.com               #
#################################################

add_executable(tp1_exercice1 exercice1.cpp)

add_executable(tp1_exercice2 exercice2.cpp)
target_link_libraries(tp1_exercice2 lib_tp1)

add_executable(tp1_exercice3 exercice3.cpp)
target_link_libraries(tp1_exercice3 lib_tp1)

add_executable(tp1_exercice4 exercice4.cpp)
target_link_libraries(tp1_exercice4 lib_tp1)

add_executable(tp1_exercice5 exercice5.cpp)
target_link_libraries(tp1_exercice5 lib_tp1)

add_executable(tp1_exercice6 exercice6.cpp)
target_link_libraries(tp1_exercice6 lib_tp1)
