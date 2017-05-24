include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

add_executable(Prog1A Prog1A.cpp)
target_link_libraries(Prog1A BaseLibA)

set_property(TARGET Prog1A PROPERTY FOLDER "Prog")

ctnSetTargetFolderProperties(Prog1A)