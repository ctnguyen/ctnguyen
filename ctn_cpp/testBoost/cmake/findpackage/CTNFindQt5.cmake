############################################################### #
#  Date             10/02/2017                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                             
#################################################################
## Include guard
if(CTNFindQt5_Include)
  return()
endif()
set(CTNFindQt5_Include TRUE)

## _Qt5Target should not contain Qt5::
## For example Qt5::Core, call ancoaCopyImportedQt5(Core "")
function(ctnCopyImportedQt5 _Qt5Target _subFolder)
    ## Copy Qt dll/so to build folder.
    get_property(_qt5_IMPORTED_LOCATION TARGET Qt5::${_Qt_Comp} PROPERTY IMPORTED_LOCATION)
    get_property(_qt5_IMPORTED_LOCATION_DEBUG TARGET Qt5::${_Qt_Comp} PROPERTY IMPORTED_LOCATION_DEBUG)
    get_property(_qt5_IMPORTED_LOCATION_RELEASE TARGET Qt5::${_Qt_Comp} PROPERTY IMPORTED_LOCATION_RELEASE)

    if(NOT CMAKE_BUILD_TYPE)# MSVC
        if(_qt5_IMPORTED_LOCATION)
            file(COPY ${_qt5_IMPORTED_LOCATION} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_subFolder})
            install(FILES ${_qt5_IMPORTED_LOCATION} DESTINATION ${_subFolder} COMPONENT AncoaFiles)
        endif()
        if(_qt5_IMPORTED_LOCATION_RELEASE)
            file(COPY ${_qt5_IMPORTED_LOCATION_RELEASE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/${_subFolder})
            install(FILES ${_qt5_IMPORTED_LOCATION_RELEASE} DESTINATION ${_subFolder} COMPONENT AncoaFiles)
        endif()
        if(_qt5_IMPORTED_LOCATION_DEBUG)
            file(COPY ${_qt5_IMPORTED_LOCATION_DEBUG} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/${_subFolder})
        endif()
    else()
        # CMAKE_BUILD_TYPE is defined and have value
        set(COPY_DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	if(_qt5_IMPORTED_LOCATION_RELEASE)
	    file(COPY ${_qt5_IMPORTED_LOCATION_RELEASE} DESTINATION ${COPY_DESTINATION}/${_subFolder})
	    install(FILES ${_qt5_IMPORTED_LOCATION_RELEASE} DESTINATION ${_subFolder} COMPONENT AncoaFiles)
	elseif(_qt5_IMPORTED_LOCATION_DEBUG)
	    file(COPY ${_qt5_IMPORTED_LOCATION_DEBUG} DESTINATION ${COPY_DESTINATION}/${_subFolder})
	    install(FILES ${_qt5_IMPORTED_LOCATION_DEBUG} DESTINATION ${_subFolder} COMPONENT AncoaFiles)
	else()
	    file(COPY ${_qt5_IMPORTED_LOCATION} DESTINATION ${COPY_DESTINATION}/${_subFolder})
	    install(FILES ${_qt5_IMPORTED_LOCATION} DESTINATION ${_subFolder} COMPONENT AncoaFiles)
	endif()
    endif()
endfunction()

set(BACKUP_CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH})
if(CUSTOM_ANCOA_QT_ROOT)
    set(CMAKE_PREFIX_PATH ${CUSTOM_ANCOA_QT_ROOT})
elseif(DEFINED ENV{QT_ROOT})
    set(CMAKE_PREFIX_PATH $ENV{QT_ROOT})
elseif(ANCOA_FRAMEWORKS_QT_ROOT)
    set(CMAKE_PREFIX_PATH {ANCOA_FRAMEWORKS_QT_ROOT})
endif()

# Set Automoc for Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
### Find all required Qt5 component here
message("  -- Ancoa try to find Qt5 in [${CMAKE_PREFIX_PATH}]")

## Add a required component here  ======================
set(Ancoa_Required_QT_COMPONENTS
    Concurrent
    Core
    Gui
    Multimedia
    Network
    PrintSupport
    OpenGL
    Sql
    WebSockets
    Widgets
    Xml
)
if(WIN32)
    set(Ancoa_Required_QT_COMPONENTS ${Ancoa_Required_QT_COMPONENTS} WinExtras)
endif()
foreach(_Qt_Comp ${Ancoa_Required_QT_COMPONENTS})
    find_package(Qt5${_Qt_Comp} REQUIRED)
endforeach()
    
foreach(_Qt_Comp ${Ancoa_Required_QT_COMPONENTS})
    ctnCopyImportedQt5(${_Qt_Comp} ".")
endforeach()

### copy dll for sql plugins ======================
set(_Qt_sql_plugins
    QPSQLDriverPlugin
    QMYSQLDriverPlugin
    QSQLiteDriverPlugin
)
foreach(_Qt_Comp ${_Qt_sql_plugins})
    ctnCopyImportedQt5(${_Qt_Comp} sqldrivers)
endforeach()

### copy dll for platforms plugins ======================
set(_Qt_GUI_plugins
    QMinimalIntegrationPlugin
    QOffscreenIntegrationPlugin
)
if(WIN32)
    set(_Qt_GUI_plugins ${_Qt_GUI_plugins} QWindowsIntegrationPlugin)
else()## Linux
    set(_Qt_GUI_plugins ${_Qt_GUI_plugins} QLinuxFbIntegrationPlugin)
endif()
foreach(_Qt_Comp ${_Qt_GUI_plugins})
    ctnCopyImportedQt5(${_Qt_Comp} platforms)
endforeach()

### TODO qt media service ======================

## A bit of hacked to point to QtSolutions
set(FRAMEWORKS_QTSOLUTIONS_SERVICE_SRC ${FRAMEWORKS_ROOT}/QtSolutions/qtservice/src)

set(CMAKE_PREFIX_PATH ${BACKUP_CMAKE_PREFIX_PATH})
message("")
