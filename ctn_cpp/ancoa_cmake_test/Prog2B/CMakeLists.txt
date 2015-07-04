include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(projNAME Prog2B)

add_executable(${projNAME} Proj2B.cpp)

target_link_libraries(${projNAME} Proj2	ProjB)

ctnSetTargetFolderProperties(${projNAME})