set(fileList 
    demo_portable_archive.cpp
    portable_binary_archive.hpp
    portable_binary_iarchive.hpp
    portable_binary_iarchive.cpp
    portable_binary_oarchive.hpp
    portable_binary_oarchive.cpp)
add_executable(demo_portable_archive ${fileList})
target_link_libraries(demo_portable_archive ${Boost_LIBRARIES})