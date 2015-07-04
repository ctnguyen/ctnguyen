include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(projNAME Proj1)

SET(projHEADERS Proj1.hpp)
SET(projSOURCES Proj1.cpp)
#SET(projMOCs mocFilesHere)
#SET(projRESOURCES resourceFileHere)

add_library(${projNAME} ${projSOURCES} ${projHEADERS})

ctnSetTargetFolderProperties(${projNAME})