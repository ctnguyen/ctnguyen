include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

add_executable(Prog2B Prog2B.cpp)
target_link_libraries(Prog2B BaseLibB)

set_property(TARGET Prog2B PROPERTY FOLDER "Prog")

install(TARGETS Prog2B RUNTIME DESTINATION App COMPONENT Prog2B)
set(CPACK_COMPONENT_PROG2B_GROUP "Programmes" CACHE STRING "")
set(CPACK_COMPONENT_PROG2B_DISPLAY_NAME "Prog 2 B" CACHE STRING "")

ctnSetTargetFolderProperties(Prog2B)