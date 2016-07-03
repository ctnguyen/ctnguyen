#define BOOST_TEST_MODULE test_Boost_SerializationAllNativeType
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <cstddef> // NULL
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

#include <boost/mpl/list.hpp>

/// TODO test all STL containers string, vector, list

struct BinaryArray
{
    /// init buffer with all 'z' char
    BinaryArray() 
    : sr(buffer, buffer_size)
    , source(sr)
    , oa(source, test_flag)
    {   
        for(size_t i=0;i<buffer_size;++i)
            buffer[i]='z';
    }
    
    size_t getUsedLength() const
    {
        size_t unusedPos=buffer_size-1;
        while(unusedPos>0 && buffer[unusedPos]=='z')
            --unusedPos;
        return ++unusedPos;
    }

    ~BinaryArray(){}

    static const size_t buffer_size =  100;
    char buffer[buffer_size];

    const boost::archive::archive_flags test_flag = boost::archive::no_header;
    boost::iostreams::basic_array_sink<char> sr;
    boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source;
    boost::archive::binary_oarchive oa;
};

BOOST_AUTO_TEST_SUITE(All_Types)

template <typename Type>
std::string getTypeInfoMessage(const Type& object)
{
    const std::string typeInfo( typeid(object).name());
    const size_t typeSize = sizeof(Type);
    std::ostringstream msgLogStream;
    msgLogStream<<"["<<typeInfo << "] size:"<<typeSize;
    const std::string msgLog = msgLogStream.str();
    return msgLog;
}

template <typename Type>
void test_serialization()
{
    BinaryArray testFixture;
    Type defaultObject;

    const std::string msgLog = getTypeInfoMessage(defaultObject);
    
    BOOST_TEST_MESSAGE(msgLog);
    
    testFixture.oa<<defaultObject;
    const size_t nbUsedChar = testFixture.getUsedLength();
    
    // TODO : check accuracy, deserialize and check

    BOOST_CHECK(nbUsedChar==sizeof(Type));
}

BOOST_AUTO_TEST_CASE(test_multi_types)
{
    //// http://en.cppreference.com/w/cpp/language/types

    test_serialization<char>();
    test_serialization<signed char>();
    test_serialization<unsigned char>();
    test_serialization<wchar_t>();
    test_serialization<char16_t>();
    test_serialization<char32_t>();

    test_serialization<size_t>();
    test_serialization<short>();
    test_serialization<short int>();
    test_serialization<signed short>();
    test_serialization<signed short int>();
    test_serialization<unsigned short>();
    test_serialization<unsigned short int>();
    
    test_serialization<int>();
    test_serialization<signed int>();
    test_serialization<unsigned int>();

    test_serialization<long int>();
    test_serialization<signed long int>();
    test_serialization<unsigned long>();
    test_serialization<long long int>();
    test_serialization<signed long long>();
    test_serialization<unsigned long long>();
    
    test_serialization<float>();
    test_serialization<double>();
    test_serialization<long double>();
}

BOOST_FIXTURE_TEST_CASE(test_empty_stdstring, BinaryArray)
{
    const std::string text;

    const std::string msgLog = getTypeInfoMessage(text);
    BOOST_TEST_MESSAGE(msgLog);
    
    oa<<text;
    const size_t nbUsedChar = getUsedLength();
}

BOOST_FIXTURE_TEST_CASE(test_stdstring, BinaryArray)
{
    const std::string text("helloworld");
    const size_t strSize = text.size();

    const std::string typeInfo(typeid(text).name());
    std::ostringstream msgLogStream; msgLogStream << "[" << typeInfo << "] size:" << strSize;
    const std::string msgLog = msgLogStream.str();
    BOOST_TEST_MESSAGE(msgLog);
    
    oa<<strSize;
    for(size_t i=0;i<strSize;++i)
    {
        const char& crCha = text[i];
        oa<<crCha;
    }
    const size_t nbUsedChar = getUsedLength();
}

BOOST_AUTO_TEST_SUITE_END()