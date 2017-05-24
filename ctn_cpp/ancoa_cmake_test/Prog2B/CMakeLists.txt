include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

add_executable(Prog2B Prog2B.cpp)
target_link_libraries(Prog2B BaseLibB)

set_property(TARGET Prog2B PROPERTY FOLDER "Prog")

ctnSetTargetFolderProperties(Prog2B)