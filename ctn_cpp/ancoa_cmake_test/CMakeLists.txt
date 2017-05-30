#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.7)

# For Visual Studio 12 2013, x64 use generator 
# cmake -G"Visual Studio 12 2013 Win64" E:\tempo\ctnguyen\ctn_cpp\ancoa_cmake_test
# "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" ancoa_cmake_test.sln /P:Configuration=Release /maxcpucount:8
# "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" ancoa_cmake_test.sln /P:Configuration=Debug /maxcpucount:8
# cmake -G"Visual Studio 12 2013 Win64" E:\tempo\ctnguyen\ctn_cpp\ancoa_cmake_test && "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" ancoa_cmake_test.sln /P:Configuration=Release /maxcpucount:8 && "C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" ancoa_cmake_test.sln /P:Configuration=Debug /maxcpucount:8
#
# cpack -C Release -G NSIS --config InstallerB-CPackConfig.cmake
# cpack -C Release -G NSIS --config InstallerA-CPackConfig.cmake
#
# Be sure that every libraries (Boost, Qt) are built in x64 version.
# Make sure to have the QT_ROOT and BOOST_ROOT defined and point to the root library
project(ancoa_cmake_test) 

# Set modules directories
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(${PROJECT_SOURCE_DIR}/cmake/SpecificBuildConfig.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/InvestigateTargetProperties.cmake)

option(BUILD_SHARED_LIBS "Build All lib in shared" ON)

# Set Automoc for Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)#Use C++11
cmake_policy(SET CMP0057 NEW)# USE IN_LIST functionality, example: if(${proj} IN_LIST PLUGIN_LIST)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)## Could be MSVC only
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "_CMakePredefinedTarget" )

include_directories(${CMAKE_SOURCE_DIR})
add_subdirectory(BaseLibA)
add_subdirectory(BaseLibB)

#add_subdirectory(ProjA)
#add_subdirectory(ProjB)

add_subdirectory(Prog1A)
add_subdirectory(Prog2B)

function(generateInstallerConfig install_type)
    set(CPACK_COMPONENTS_ALL Core)
    if(${install_type} STREQUAL "A")
        message("Create packaging configuration for install_type[A]")
        set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} Prog1A)
    elseif(${install_type} STREQUAL "B")
        message("Create packaging configuration for install_type[B]")
        set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} Prog2B)
    else()
        message("Cannot create configuration for install_type[${install_type}]")
    endif()
    set(CPACK_OUTPUT_CONFIG_FILE "${CMAKE_BINARY_DIR}/Installer${install_type}-CPackConfig.cmake")
    set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "${CMAKE_BINARY_DIR}/Installer${install_type}-CPackSourceConfig.cmake")
    set(CPACK_PACKAGE_FILE_NAME "installer${install_type}_CPACK_PACKAGE_FILE_NAME")
    include(CPack)
endfunction()

generateInstallerConfig("A")
generateInstallerConfig("B")

## Get source files from a target
get_property(sourcelistBaseLibA TARGET BaseLibA PROPERTY SOURCES)
get_property(sourcelistProg2B TARGET Prog2B PROPERTY SOURCES)
message("== List source files of BaseLibA [${sourcelistBaseLibA}]")
message("== List source files of   Prog2B [${sourcelistProg2B}]")

## Find Qt, if found, add this projects
##list(APPEND CMAKE_MODULE_PATH "C:/development/frameworks/qt/5.3.1/lib/cmake")
#add_subdirectory(ProjQtTest)
#add_subdirectory(ProgQt)
#echo_target(ProgQt)#TARGET information from sub dir can be populated to root

# if found boost test framework, go into the test folder
#find_package(Boost COMPONENTS)
## Attention to the structure of the boost library that has 
## ${BOOST_ROOT}/boost         all include here
## ${BOOST_ROOT}/lib           all lib and dll here
if(Boost_FOUND)
    include(CTest)
    include_directories(${Boost_INCLUDE_DIRS})
    add_subdirectory(Test)
endif()