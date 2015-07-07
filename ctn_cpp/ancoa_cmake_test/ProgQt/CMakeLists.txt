include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(projNAME ProgQt)

add_executable(${projNAME} ProgQt.cpp)

#target_link_libraries(${projNAME} Proj1	ProjA)

ctnSetTargetFolderProperties(${projNAME})