include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)
set(CTN_PROJECT_NAME Prog2B)

link_directories(${CMAKE_BINARY_DIR}/Proj2 ${CMAKE_BINARY_DIR}/ProjB)

add_executable(${CTN_PROJECT_NAME} Proj2B.cpp)

target_link_libraries(${CTN_PROJECT_NAME} Proj2 ProjB)

ctnSetTargetFolderProperties(${CTN_PROJECT_NAME})