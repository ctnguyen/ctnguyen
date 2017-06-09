# Create package by component 
# install_type can be A or B
# usage : 
#
# generateInstallerConfig("A")
# generateInstallerConfig("B")

function(generateInstallerConfig install_type)
    #set(CPACK_SET_DESTDIR ON)
    #set(CPACK_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/Installation/${install_type}/Files)
    #set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/Installation/${install_type}/Files)
    install(CODE "message(\" ========================================================= CPACK_TOPLEVEL_TAG[\${CPACK_TOPLEVEL_TAG}]\")" COMPONENT Core)
    install(CODE "message(\" ========================================================= CPACK_PACKAGING_INSTALL_PREFIX[\${CPACK_PACKAGING_INSTALL_PREFIX}]\")" COMPONENT Core)
    install(CODE "message(\" ========================================================= CPACK_PACKAGE_INSTALL_DIRECTORY[\${CPACK_PACKAGE_INSTALL_DIRECTORY}]\")" COMPONENT Core)
    install(CODE "message(\" ========================================================= CPACK_INSTALL_PREFIX[\${CMAKE_INSTALL_PREFIX}]\")" COMPONENT Core)
    install(CODE "message(\" ========================================================= CMAKE_INSTALL_PREFIX[\${CMAKE_INSTALL_PREFIX}]\")" COMPONENT Core)
    install(CODE "message(\" ========================================================= CPACK_PACKAGE_DEFAULT_LOCATION[\${CPACK_PACKAGE_DEFAULT_LOCATION}]\")" COMPONENT Core)
    install(CODE "message(\" ========================================================= CPACK_GENERATOR[${CPACK_GENERATOR}]\")" COMPONENT Core)
    
    ## https://stackoverflow.com/questions/6712000/cmake-cpack-package-installation-path-nightmare
    install(CODE "message(\" ========================================================= DESTDIR[\${DESTDIR}]\")" COMPONENT Core)
    install(CODE "message(\" =========================================================Core CPACK_INSTALL_PREFIX[\${CMAKE_INSTALL_PREFIX}]\")" COMPONENT Core)
    install(CODE "message(\" =========================================================Prog1A CPACK_INSTALL_PREFIX[\${CMAKE_INSTALL_PREFIX}]\")" COMPONENT Prog1A)
    install(CODE "message(\" =========================================================Prog2B CPACK_INSTALL_PREFIX[\${CMAKE_INSTALL_PREFIX}]\")" COMPONENT Prog2B)
    install(CODE "message(\" ======\")" COMPONENT Core)
    install(CODE "message(\" ======\")" COMPONENT Core)
    
#    include (InstallRequiredSystemLibraries)
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