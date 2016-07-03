#define BOOST_TEST_MODULE test_Boost_SerializationAllNativeType
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <cstddef> // NULL
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/archive/tmpdir.hpp>
//
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/basic_archive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

/* todo the tests

bool
(unsigned,signed) char
wchar_t
(unsigned) short
(unsigned) int
(unsigned) long
[(unsigned) long long]

float
double
[long double]

*/

void test_char_array_archive_string1()
{
    //const size_t buffer_size = 50;
    //char buffer[buffer_size];
    //for(size_t i=0;i<buffer_size;++i)
    //    buffer[i]='z';

    //boost::archive::archive_flags test_flag = boost::archive::no_header;
    //{
    //    boost::iostreams::basic_array_sink<char> sr(buffer, buffer_size);
    //    boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source(sr);
    //    boost::archive::binary_oarchive oa(source, test_flag);

    //    const size_t sizeString = sizeof(std::string);
    //    
    //    /// first byte serialized for std::string is the number of characters
    //    string1 string_wrapper;
    //    string_wrapper.value="helloworlds";
    //    oa << string_wrapper;
    //}

    //{
    //    boost::iostreams::basic_array_source<char> sr(buffer, buffer_size);
    //    boost::iostreams::stream< boost::iostreams::basic_array_source<char> > source(sr);
    //    boost::archive::binary_iarchive oa(source, test_flag);
    //    string1 string_wrapper;
    //    oa >> string_wrapper;
    //}
    //const int abc=100;
}
BOOST_AUTO_TEST_SUITE(All_Types)

BOOST_AUTO_TEST_CASE(first_test)
{
    //test_char_array_archive_stdstring();
    test_char_array_archive_string1();
    //test_char_array_archive_nativeCpp();
    //test_char_array_archive_customClasses();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()