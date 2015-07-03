include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(CTN_PROJECT_NAME Prog1A)

link_directories(${CMAKE_BINARY_DIR}/Proj1 ${CMAKE_BINARY_DIR}/ProjA)

add_executable(${CTN_PROJECT_NAME} Proj1A.cpp)

target_link_libraries(${CTN_PROJECT_NAME} Proj1	ProjA)

ctnSetTargetFolderProperties(${CTN_PROJECT_NAME})