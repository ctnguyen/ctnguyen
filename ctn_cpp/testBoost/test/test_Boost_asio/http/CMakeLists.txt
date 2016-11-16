#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 3.2)

# cmake path/to/source/folder/ -G"Visual Studio 12 2013 Win64"
# cmake path/to/source/folder/ -G"Eclipse CDT4 - Unix Makefiles"
# cmake path/to/source/folder/ -G"CodeBlocks – Unix Makefiles"

add_definitions(-DBOOST_ALL_DYN_LINK) # Use boost dll versions, lib without lib prefix
find_package(Boost REQUIRED COMPONENTS system date_time regex)
message("                       Boost_INCLUDE_DIR [${Boost_INCLUDE_DIR}]")
message("                      Boost_INCLUDE_DIRS [${Boost_INCLUDE_DIRS}]")
message("                         Boost_LIBRARIES [${Boost_LIBRARIES}]")
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES
    connection.cpp                                                                                                                                   
    connection.hpp                                                                                                                                   
    connection_manager.cpp                                                                                                                           
    connection_manager.hpp                                                                                                                           
    header.hpp                                                                                                                                       
    main.cpp                                                                                                                                         
    mime_types.cpp                                                                                                                                   
    mime_types.hpp                                                                                                                                   
    reply.cpp                                                                                                                                        
    reply.hpp                                                                                                                                        
    request.hpp                                                                                                                                      
    request_handler.cpp                                                                                                                              
    request_handler.hpp                                                                                                                              
    request_parser.cpp                                                                                                                               
    request_parser.hpp                                                                                                                               
    server.cpp                                                                                                                                       
server.hpp
) 

add_executable(http ${SOURCE_FILES})
target_link_libraries(http ${Boost_LIBRARIES})
set_property(TARGET http PROPERTY FOLDER "test/http")
## TODO : automatic copy index.html alongside build executable.