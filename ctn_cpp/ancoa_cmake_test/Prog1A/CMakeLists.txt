include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

add_executable(Prog1A Prog1A.cpp)
target_link_libraries(Prog1A BaseLibA)

set_property(TARGET Prog1A PROPERTY FOLDER "Prog")

install(TARGETS Prog1A RUNTIME DESTINATION App COMPONENT Prog1A)
set(CPACK_COMPONENT_PROG1A_GROUP "Programmes" CACHE STRING "")
set(CPACK_COMPONENT_PROG1A_DISPLAY_NAME "Prog 1 A" CACHE STRING "")

ctnSetTargetFolderProperties(Prog1A)