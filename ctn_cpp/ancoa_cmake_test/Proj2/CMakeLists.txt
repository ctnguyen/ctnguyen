include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(projNAME Proj2)

SET(projHEADERS Proj2.hpp)
SET(projSOURCES Proj2.cpp)
#SET(projMOCs mocFilesHere)
#SET(projRESOURCES resourceFileHere)

add_library(${projNAME} ${projSOURCES} ${projHEADERS})

ctnSetTargetFolderProperties(${projNAME})