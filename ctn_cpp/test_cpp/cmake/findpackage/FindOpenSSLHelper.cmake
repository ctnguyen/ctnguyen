############################################################### #
#  Date             03/07/2018                                  #
#  Creator          Chi Thanh NGUYEN                            #
#  Authors          Chi Thanh NGUYEN                            #
#                                                               #
#  Copyright (c) 2018 CTN.   All rights reserved                #
#################################################################
## Include guard
if(FindOpenSSLHelper_Include)
  return()
endif()
set(FindOpenSSLHelper_Include TRUE)

if(NOT DEBUG_FIND_OPENSSL_HELPER)
    set(DEBUG_FIND_OPENSSL_HELPER OFF)# Set to ON if want to debug
endif()
include(${SOURCE_ROOT_DIR}/cmake/findpackage/FindPackageHelper.cmake)

## For Windows, download binary prebuilt OpenSSL and set %OPENSSL_ROOT_DIR% pointing to the root of the installed directory
##
## For Linux, build from source using the command :
##     ./config shared --prefix=/path/to/installed/directory --openssldir=/path/to/installed/directory && make depend && make -j8 && make test && make install
## set $OPENSSL_ROOT_DIR pointing to the root of the installed directory 

find_package(OpenSSL)

if(OPENSSL_FOUND) ## hack to copy shared library to executable directory
    message("OPENSSL_INCLUDE_DIR [${OPENSSL_INCLUDE_DIR}]")
    get_filename_component(_OPENSSL_ROOT ${OPENSSL_INCLUDE_DIR} DIRECTORY)
    if(WIN32)
        set(_OPENSSL_BIN "${_OPENSSL_ROOT}/bin")
        file(GLOB_RECURSE _dll_files ${_OPENSSL_BIN}/lib*.dll)
        set(_CONFIGS DEBUG RELEASE)
        foreach(_CONFIG ${_CONFIGS})
            set(_PATH_OF_COPY_DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_CONFIG}})
            foreach(_dll ${_dll_files})
                file(COPY ${_dll} DESTINATION ${_PATH_OF_COPY_DESTINATION})
                install(FILES ${_dll} DESTINATION "." COMPONENT Files)
            endforeach()
        endforeach()
    else()
        makeTargetNoSymlink("OpenSSL" "Crypto" "")
        copyImportedSharedLibrary("OpenSSL" "Crypto" ".")
        makeTargetNoSymlink("OpenSSL" "SSL" "")
        copyImportedSharedLibrary("OpenSSL" "SSL" ".")
        # Hack to copy files lib*.*.*.*. The imported target are libssl.* and libcrypto.*, but those depend to libssl.1.1.* and libcrypto.1.1.*
        set(_OPENSSL_UNIX_LIB_DIR "${_OPENSSL_ROOT}/lib")
        file(GLOB_RECURSE _dynamic_libs ${_OPENSSL_UNIX_LIB_DIR}/lib*.*.*.*)
        foreach(_lib ${_dynamic_libs})
            file(COPY ${_lib} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
            install(FILES ${_lib} DESTINATION "." COMPONENT Files)
        endforeach()
    endif()
    
    #copy and install ssl certificate (default one of python) ## todo refactor this code to FindPackageHelper.cmake to have reusability
    set(PY_SSL_CERT_FILE ${CMAKE_SOURCE_DIR}/cmake/findpackage/pycacert.pem)
    if(NOT EXISTS ${PY_SSL_CERT_FILE})
        message(FATAL_ERROR "Not found expected file [${PY_SSL_CERT_FILE}]")
    endif()

    if(NOT CMAKE_BUILD_TYPE)# MSVC
        file(COPY ${PY_SSL_CERT_FILE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
        file(COPY ${PY_SSL_CERT_FILE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
    else()
        file(COPY ${PY_SSL_CERT_FILE} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endif()
    install(FILES ${PY_SSL_CERT_FILE} DESTINATION "." COMPONENT Files)

endif()

function(print_openssl_info)
    echo_target(OpenSSL::Crypto)
    echo_target(OpenSSL::SSL)
    
    message("OPENSSL_INCLUDE_DIR [${OPENSSL_INCLUDE_DIR}]")
    message("OPENSSL_CRYPTO_LIBRARY [${OPENSSL_CRYPTO_LIBRARY}]")
    message("OPENSSL_SSL_LIBRARY [${OPENSSL_SSL_LIBRARY}]")
    message("OPENSSL_LIBRARIES [${OPENSSL_LIBRARIES}]")
endfunction()
