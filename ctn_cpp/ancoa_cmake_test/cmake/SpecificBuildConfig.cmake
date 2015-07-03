function(check64Bit resultHolder)

	if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		set(${resultHolder} ON PARENT_SCOPE) 
	else()
		set(${resultHolder} OFF PARENT_SCOPE) 
	endif()

endfunction()

function(getRootBuildFolder resultPathHolder)
    
    set(pathRootBuildFolder "${CMAKE_BINARY_DIR}") # initialize path for build folder to binary directory

    if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		set(pathRootBuildFolder "${pathRootBuildFolder}/x64")
	else()
		set(pathRootBuildFolder "${pathRootBuildFolder}/x86")
	endif()

    set(${resultPathHolder} "${pathRootBuildFolder}" PARENT_SCOPE) 
endfunction()



function(ctnSetTargetFolderProperties targetName)

    getRootBuildFolder(pathToRootBuildFolder)

    foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
        string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
        set_target_properties( ${targetName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${pathToRootBuildFolder}/${OUTPUTCONFIG}" )
        set_target_properties( ${targetName} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${pathToRootBuildFolder}/${OUTPUTCONFIG}" )
        set_target_properties( ${targetName} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${pathToRootBuildFolder}/${OUTPUTCONFIG}" )
    endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
endfunction()