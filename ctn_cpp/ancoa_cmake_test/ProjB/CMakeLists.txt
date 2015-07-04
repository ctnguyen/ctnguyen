include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(projNAME ProjB)

SET(projHEADERS ProjB.hpp)
SET(projSOURCES ProjB.cpp)
#SET(projMOCs mocFilesHere)
#SET(projRESOURCES resourceFileHere)

add_library(${projNAME} ${projSOURCES} ${projHEADERS})

ctnSetTargetFolderProperties(${projNAME})