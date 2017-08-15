set(fileList 
    demo_portable_archive.cpp
    portable_binary_archive.hpp
    portable_binary_iarchive.hpp
    portable_binary_iarchive.cpp
    portable_binary_oarchive.hpp
    portable_binary_oarchive.cpp)
add_executable(demo_portable_archive ${fileList})
target_compile_definitions(demo_portable_archive PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
target_link_libraries(demo_portable_archive Boost::serialization Boost::iostreams Boost::unit_test_framework)