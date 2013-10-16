#################################################
#                                               #
#   C++ PROGRAMMING                             #
#   MASTER LAURE ELIE 2013-2014                 #
#   Student Chi Thanh NGUYEN                    # 
#                                               #
#   chithanhnguyen.math@gmail.com               #
#################################################

add_executable(exercice1_tp1 exercice1.cpp)

add_executable(exercice2_tp1 exercice2.cpp)
target_link_libraries(exercice2_tp1 lib_tp1)

add_executable(exercice3_tp1 exercice3.cpp)
target_link_libraries(exercice3_tp1 lib_tp1)

add_executable(exercice4_tp1 exercice4.cpp)
target_link_libraries(exercice4_tp1 lib_tp1)

add_executable(exercice5_tp1 exercice5.cpp)
target_link_libraries(exercice5_tp1 lib_tp1)

add_executable(exercice6_tp1 exercice6.cpp)
target_link_libraries(exercice6_tp1 lib_tp1)
