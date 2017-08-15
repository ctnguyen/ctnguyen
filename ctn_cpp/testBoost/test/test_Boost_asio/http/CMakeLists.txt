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
target_compile_definitions(http PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
target_link_libraries(http Boost::date_time Boost::regex Boost::system)
set_property(TARGET http PROPERTY FOLDER "test/Boost_Asio")
## TODO : automatic copy index.html alongside build executable.