include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

SET(projHEADERS BaseLibB.hpp BaseLibBSymbols.hpp)
SET(projSOURCES BaseLibB.cpp)

add_library(BaseLibB SHARED ${projSOURCES} ${projHEADERS})

## Set folder structure in IDE
set_property(TARGET BaseLibB PROPERTY FOLDER "Core")

target_compile_definitions(BaseLibB PRIVATE BaseLibB_EXPORT)

## Set folder for build target
ctnSetTargetFolderProperties(BaseLibB)