include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(projNAME ProjA)

SET(projHEADERS ProjA.hpp ProjASharedDefinition.hpp)
SET(projSOURCES ProjA.cpp)
#SET(projMOCs mocFilesHere)
#SET(projRESOURCES resourceFileHere)

add_library(${projNAME} ${projSOURCES} ${projHEADERS})

ctnSetTargetFolderProperties(${projNAME})