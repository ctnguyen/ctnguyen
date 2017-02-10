include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/InvestigateTargetProperties.cmake)
## Help to find Qt5, Only set it in the leaf level of project hierachy
set(CMAKE_PREFIX_PATH $ENV{QT_ROOT})

set(projHEADERS 
	${CMAKE_CURRENT_SOURCE_DIR}/MocTester.hpp)

set(projSOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/MocTester.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/ProgQt.cpp)

set(projNAME ProgQtt)

add_executable(${projNAME} ${projHEADERS} ${projSOURCES})

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
target_link_libraries(${projNAME} Qt5::Widgets)
ctnSetTargetFolderProperties(${projNAME})

#echo_target(Qt5::Widgets)



