include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(projNAME ProjQtTest)

SET(projHEADERS ProjQtTest.hpp ProjQtTestSharedDefinition.hpp)
SET(projSOURCES ProjQtTest.cpp)
#SET(projMOCs mocFilesHere)
#SET(projRESOURCES resourceFileHere)

add_library(${projNAME} ${projSOURCES} ${projHEADERS})

ctnSetTargetFolderProperties(${projNAME})