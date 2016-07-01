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
        oa <<onecharObj1 <<chartoserialize[0] <<oneintObj << chartoserialize[1]<<onecharObj2;
    }


    const int abc=100;
}

int main(int argc, char *argv[])
{

    test_char_array_archive_nativeCpp();
    test_char_array_archive_customClasses();

    const int i=100;
    return 0;
}