#define BOOST_TEST_MODULE test_Boost_Serialization_TypeTracking
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
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/level.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include <boost/mpl/list.hpp>

/// TODO test all STL containers string, vector, list

//// Test use no tracking inheritance
//// http://stackoverflow.com/questions/15614093/derived-class-serialization-without-class-tracking-in-boost-c

struct BinaryArray
{
    /// init buffer with all 'z' char
    BinaryArray() 
    : bsink(buffer, buffer_size)
    , bsource(buffer, buffer_size)
    , sink(bsink)
    , source(bsource)
    , oa(sink, test_flag)
    , ia(source, test_flag)
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
    boost::iostreams::basic_array_sink<char> bsink;
    boost::iostreams::basic_array_source<char> bsource;
    boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > sink;
    boost::iostreams::stream< boost::iostreams::basic_array_source<char> > source;
    boost::archive::binary_oarchive oa;
    boost::archive::binary_iarchive ia;
};

struct MyClassWithTrack
{
    char mValue;
    template<class Archive> void serialize(Archive & ar, const unsigned int version) { ar & mValue; }

    bool operator==( const MyClassWithTrack& crOther) const { return crOther.mValue==mValue; }
};

struct MyClassNoTrack
{
    char mValue;
    template<class Archive> void serialize(Archive & ar, const unsigned int version) { ar & mValue; }

    bool operator==( const MyClassNoTrack& crOther) const { return crOther.mValue==mValue; }
};
/// To not use extra byte to track for custom class, use this BOOST_CLASS_IMPLEMENTATION macro
/// That way, we have full control of the size of data and the serialization size.
BOOST_CLASS_IMPLEMENTATION(MyClassNoTrack, boost::serialization::primitive_type)

BOOST_AUTO_TEST_SUITE(All_Types)

BOOST_FIXTURE_TEST_CASE(test_with_track, BinaryArray)
{
    MyClassWithTrack mObjectInit;
    mObjectInit.mValue = 'a';
    {   
        oa << mObjectInit;
    }

    {
        MyClassWithTrack mObjectAfter;
        mObjectAfter.mValue = 'b';
        ia >> mObjectAfter;
        BOOST_CHECK(mObjectInit==mObjectAfter);
    }

    const size_t nbExtraBytesForSavedClassInfo = 5;// Boost.Serialization use 5 extra bytes suffix to store class info/tracking
    const size_t nbUsedChar = getUsedLength();
    BOOST_CHECK(nbUsedChar== sizeof(MyClassWithTrack)+nbExtraBytesForSavedClassInfo);
}

BOOST_FIXTURE_TEST_CASE(test_no_track, BinaryArray)
{
    MyClassNoTrack mObjectInit;
    mObjectInit.mValue = 'a';
    {   
        oa << mObjectInit;
    }

    {
        MyClassNoTrack mObjectAfter;
        mObjectAfter.mValue = 'b';
        ia >> mObjectAfter;
        BOOST_CHECK(mObjectInit==mObjectAfter);
    }

    const size_t nbUsedChar = getUsedLength();
    const size_t classSize = sizeof(MyClassNoTrack);
    BOOST_CHECK(nbUsedChar== classSize);// Class with Track Info have 0 extra bytes
}

BOOST_AUTO_TEST_SUITE_END()