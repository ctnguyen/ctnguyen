add_executable(allocation allocation.cpp)
target_compile_definitions(allocation PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
target_link_libraries(allocation Boost::system Boost::date_time Boost::regex)
set_property(TARGET allocation PROPERTY FOLDER "test/Boost_Asio")