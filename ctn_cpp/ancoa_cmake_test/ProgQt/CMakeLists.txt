include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/InvestigateTargetProperties.cmake)

set(projHEADERS 
	${CMAKE_CURRENT_SOURCE_DIR}/MocTester.hpp)

set(projSOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/MocTester.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/ProgQt.cpp)

set(projNAME ProgQt)

add_executable(${projNAME} ${projHEADERS} ${projSOURCES})

## Help to find Qt5, Only set it in the leaf level of project hierachy, i.e build a target
set(CMAKE_PREFIX_PATH $ENV{QT_ROOT})
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
target_link_libraries(${projNAME} Qt5::Core Qt5::Widgets)
ctnSetTargetFolderProperties(${projNAME})
### Add here a function call on Qt5:: imported target. It will copy the Qt dll or so to the build folder 
### Where there're all executables
#handleQtSharedLib(Qt5::Core)
#handleQtSharedLib(Qt5::Widgets)

echo_target(Qt5::Widgets)



