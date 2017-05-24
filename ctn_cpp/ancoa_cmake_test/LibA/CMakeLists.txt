include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

SET(projHEADERS BaseLibA.hpp BaseLibASymbols.hpp)
SET(projSOURCES BaseLibA.cpp)

add_library(BaseLibA SHARED ${projSOURCES} ${projHEADERS})

## Set folder structure in IDE
set_property(TARGET BaseLibA PROPERTY FOLDER "Core")

target_compile_definitions(BaseLibA PRIVATE BaseLibA_EXPORT)

## Set folder for build target
ctnSetTargetFolderProperties(BaseLibA)