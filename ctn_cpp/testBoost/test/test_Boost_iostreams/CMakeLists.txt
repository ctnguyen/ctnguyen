add_executable(test_Boost_IostreamsPerformance test_Boost_IostreamsPerformance.cpp)
target_compile_definitions(test_Boost_IostreamsPerformance PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
target_link_libraries(test_Boost_IostreamsPerformance Boost::iostreams Boost::filesystem Boost::system Boost::unit_test_framework)
add_test(test_Boost_IostreamsPerformance test_Boost_IostreamsPerformance)
set_property(TARGET test_Boost_IostreamsPerformance PROPERTY FOLDER "test/Boost_Iostreams")

#add_executable(large_file_test large_file_test.cpp)
#target_compile_definitions(large_file_test PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
#target_link_libraries(large_file_test Boost::iostreams Boost::filesystem Boost::system Boost::unit_test_framework)

#add_executable(mapped_file_test constants.hpp temp_file.hpp verification.hpp mapped_file_test.cpp)
#target_compile_definitions(mapped_file_test PUBLIC BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
#target_link_libraries(mapped_file_test Boost::iostreams Boost::filesystem Boost::system Boost::unit_test_framework)