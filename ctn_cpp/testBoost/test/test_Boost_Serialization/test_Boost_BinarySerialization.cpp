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


struct OneChar
{
public:
    OneChar(): mA('a'){}

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) { ar & mA; }
    char mA;
};

struct OneInt
{
public:
    OneInt(): mInt(1){}
    template<class Archive> void serialize(Archive & ar, const unsigned int version) { ar & mInt; }
    int mInt;
};

struct CharInt
{
public:
    CharInt():mA('a'), mInt(1){}
    template<class Archive> void serialize(Archive & ar, const unsigned int version) { ar & mA & mInt; }
    char mA;
    int mInt;
};

struct string1 //Todo reduce the overhead 8byte preprend to be 1byte prepend only
{
    bool empty() const  { return value.empty();}
    size_t size() const { return value.size();}
    size_t length () const { return value.length();}
    char& operator[](size_t i){ return value[i];}
    const char& operator[](size_t i) const { return value[i];}
    std::string value;

    template<class Archive> 
    void serialize(Archive & ar, const unsigned int version) 
    {
        ar& value;
    }
};

void test_char_array_archive_stdstring()
{
    /// boost serialization is not optimal, there are overhead in serialized data to stored information
    /// of the class, that's necessary to deserialize data latter.
    /// For std::string, there are 8bytes overhead to write before string data. That much of overhead is to handle large string.
    /// So a customized std::string class would be done to store optimally for different categories of str
    /// string1 use 1 byte overhead : upto 256 characters
    /// string2 use 2 byte overhead : upto 65536 characters

    const size_t buffer_size = 1000;
    char buffer[buffer_size];
    for(size_t i=0;i<buffer_size;++i)
        buffer[i]='z';

    boost::archive::archive_flags test_flag = boost::archive::no_header;
    {
        boost::iostreams::basic_array_sink<char> sr(buffer, buffer_size);
        boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source(sr);
        boost::archive::binary_oarchive oa(source, test_flag);

        const size_t sizeString = sizeof(std::string);
        
        /// first byte serialized for std::string is the number of characters
        std::string helloWord="helloworlds";
        oa & helloWord;

        std::string verylongString(129,'a');
        oa & verylongString;
    }

    const int abc=100;
}

void test_char_array_archive_string1()
{
    const size_t buffer_size = 1000;
    char buffer[buffer_size];
    for(size_t i=0;i<buffer_size;++i)
        buffer[i]='z';

    boost::archive::archive_flags test_flag = boost::archive::no_header;
    {
        boost::iostreams::basic_array_sink<char> sr(buffer, buffer_size);
        boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source(sr);
        boost::archive::binary_oarchive oa(source, test_flag);

        const size_t sizeString = sizeof(std::string);
        
        /// first byte serialized for std::string is the number of characters
        string1 string_wrapper;
        string_wrapper.value="helloworlds";
        oa << string_wrapper;
    }

    {
        boost::iostreams::basic_array_source<char> sr(buffer, buffer_size);
        boost::iostreams::stream< boost::iostreams::basic_array_source<char> > source(sr);
        boost::archive::binary_iarchive oa(source, test_flag);
        string1 string_wrapper;
        oa >> string_wrapper;
    }
    const int abc=100;
}

void test_char_array_archive_nativeCpp()
{
    /// boost serialization is not optimal, there are overhead 
    /// between objects
    /// will need to create custom archive
    /// http://stackoverflow.com/questions/3921151/creating-own-implementation-of-boostarchive
    /// http://stackoverflow.com/questions/26336414/serializing-object-to-byte-array-in-c

    const size_t buffer_size =  100;
    char buffer[buffer_size];
    for(size_t i=0;i<buffer_size;++i)
        buffer[i]='z';

    //AZ p0('a','b','c','d','e');
    //XY p1('A','B');
    ////XY p1('b','Y');
    //XYZ p2('C','D','E');
    boost::archive::archive_flags test_flag = boost::archive::no_header;

    {

        boost::iostreams::basic_array_sink<char> sr(buffer, buffer_size);
        boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source(sr);
        boost::archive::binary_oarchive oa(source, test_flag);
        //boost::archive::binary_oarchive oa(source, boost::archive::no_tracking);
        
        char chartoserialize[2];
        chartoserialize[0]='x';
        chartoserialize[1]='y';
        
        int inttoserialize[2];
        inttoserialize[0]=128;
        inttoserialize[1]=1;
        const size_t sizeChar = sizeof(char);
        const size_t sizeInt = sizeof(int);
        const size_t sizeUInt = sizeof(unsigned int);
        const size_t sizeString = sizeof(std::string);

        std::string ab1 = "ab";
        std::string xy1 = "rpqxy";

        oa & chartoserialize[0] & inttoserialize[1] & ab1 & xy1;
    }

    const int abc=100;
}


//http://stackoverflow.com/questions/20548983/boost-serialization-version-information
#include <boost/serialization/level.hpp>
//BOOST_CLASS_IMPLEMENTATION(std::string, boost::serialization::object_serializable);
BOOST_CLASS_IMPLEMENTATION(OneChar, boost::serialization::object_serializable);
BOOST_CLASS_IMPLEMENTATION(OneInt, boost::serialization::object_serializable);
BOOST_CLASS_IMPLEMENTATION(CharInt, boost::serialization::object_serializable);

void test_char_array_archive_customClasses()
{
    /// boost serialization is not optimal, there are overhead 
    /// between objects
    /// will need to create custom archive
    /// http://stackoverflow.com/questions/3921151/creating-own-implementation-of-boostarchive
    /// http://stackoverflow.com/questions/26336414/serializing-object-to-byte-array-in-c

    const size_t buffer_size =  100;
    char buffer[buffer_size];
    for(size_t i=0;i<buffer_size;++i)
        buffer[i]='z';

    //AZ p0('a','b','c','d','e');
    //XY p1('A','B');
    ////XY p1('b','Y');
    //XYZ p2('C','D','E');
    boost::archive::archive_flags test_flag = boost::archive::no_header;

    {

        boost::iostreams::basic_array_sink<char> sr(buffer, buffer_size);
        boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source(sr);
        boost::archive::binary_oarchive oa(source, test_flag);
        //boost::archive::binary_oarchive oa(source, boost::archive::no_tracking);
        
        char chartoserialize[2];
        chartoserialize[0]='I';
        chartoserialize[1]='I';
        
        int inttoserialize[1];
        inttoserialize[0]=128;

        std::string ab = "ab";

        //oa << chartoserialize[0] << inttoserialize[0] << chartoserialize[1] << ab;

        const size_t sizeOneChar = sizeof(OneChar);
        const size_t sizeOneInt = sizeof(OneInt);
        const size_t sizeCharInt = sizeof(CharInt);

        OneChar onecharObj1, onecharObj2;
        onecharObj1.mA='X';onecharObj2.mA='Y';
        OneInt oneintObj;
        CharInt charintObj;
        oa <<onecharObj1 << chartoserialize[0];
        //oa <<onecharObj1 <<chartoserialize[0] <<oneintObj << chartoserialize[1]<<onecharObj2;
    }


    const int abc=100;
}

int main(int argc, char *argv[])
{
    //test_char_array_archive_stdstring();
    test_char_array_archive_string1();
    //test_char_array_archive_nativeCpp();
    //test_char_array_archive_customClasses();

    const int i=100;
    return 0;
}