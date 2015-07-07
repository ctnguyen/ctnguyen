include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)

set(projNAME ProgQt)

add_executable(${projNAME} ProgQt.cpp)

set(CMAKE_PREFIX_PATH "C:/development/frameworks/qt/5.3.1")
find_package(Qt5Core)
find_package(Qt5Widgets)
#find_package(Qt5Widgets)
#get_target_property(QtWidgets_location Qt5::Widgets LOCATION)
target_link_libraries(${projNAME} Qt5::Widgets)


#get_target_property(QtCore_location Qt5::Core LOCATION)


ctnSetTargetFolderProperties(${projNAME})