include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(projNAME Prog1A)

add_executable(${projNAME} Proj1A.cpp)

target_link_libraries(${projNAME} Proj1	ProjA)

ctnSetTargetFolderProperties(${projNAME})