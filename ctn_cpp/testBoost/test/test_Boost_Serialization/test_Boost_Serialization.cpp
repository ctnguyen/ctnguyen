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

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

class XY
{
public:
    XY(): mX('a'),mY('a'){}

    XY(const char& crX, const char& crY) : mX(crX), mY(crY) {}
    
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & mX;
        ar & mY;
    }

    ///
    char mX;
    char mY;
};

class XYZ
{
public:
    XYZ(): mX('a'),mY('a'),mZ('a'){}

    XYZ(const char& crX, const char& crY, const char& crZ) : mX(crX), mY(crY), mZ(crZ) {}
    
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & mX;
        ar & mY;
        ar & mZ;
    }

    ///
    char mX;
    char mY;
    char mZ;
};

class AZ
{
public:
    AZ():mXY(),mXYZ(){}
    AZ(const char& l0, const char& l1, const char& l2, const char& l3, const char& l4)
        :mXY(l0,l1),mXYZ(l2,l3,l4){}
private:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & mXY;
        ar & mXYZ;
    }

    XY mXY;
    XYZ mXYZ;

};

class TradePoint
{
public:
    TradePoint(): mID(0),mLabel("DefaultLabel"), mX(0.), mY(0.){}

    TradePoint(const unsigned int id, const std::string& crLabel, const double& crX, const double& crY) : mID(id),mLabel(crLabel), mX(crX), mY(crY) {}

    const std::string& getLabel() const { return mLabel; }
    unsigned int getID()          const { return mID;}
    const double& getX()          const { return mX; }
    const double& getY()          const { return mY; }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & mID;
        ar & mLabel;
        ar & mX;
        ar & mY;
    }
    friend std::ostream & operator<<(std::ostream &os, const TradePoint& crTradePoint)
    { 
        os<<crTradePoint;
        return os;
    }

    ///
    unsigned int mID;
    std::string mLabel;
    double mX;
    double mY;
};

void test_text_archive()
{
    const std::string filename = "hello.txt";
    TradePoint p0(1,"hello",100.,100.);
    std::ofstream ofs(filename);
    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << p0;
    	// archive and stream closed when destructors are called
    }

    TradePoint p1;
    {
        // create and open an archive for input
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> p1;
        // archive and stream closed when destructors are called
    }
}

void test_binary_archive()
{
    const std::string filename = "hello.data";
    TradePoint p0(1,"hello",100.,100.);
    std::ofstream ofs(filename);
    // save data to archive
    {
        boost::archive::binary_oarchive oa(ofs);
        // write class instance to archive
        oa << p0;
    	// archive and stream closed when destructors are called
    }

    TradePoint p1;
    {
        // create and open an archive for input
        std::ifstream ifs(filename);
        boost::archive::binary_iarchive ia(ifs);
        // read class state from archive
        ia >> p1;
        // archive and stream closed when destructors are called

        //std::cout<<p1<<std::endl; // TODO
    }
}

void test_char_array_archive()
{
    /// boost serialization is not optimal, there are overhead 
    /// between objects
    /// will need to create custom archive
    /// http://stackoverflow.com/questions/3921151/creating-own-implementation-of-boostarchive
    /// http://stackoverflow.com/questions/26336414/serializing-object-to-byte-array-in-c

    const size_t buffer_size =  100;
    char buffer[buffer_size];
    for(size_t i=0;i<buffer_size;++i)
        buffer[i]='k';

    //XY p0('a','Z');
    //XY p1('b','Y');
    //XYZ p3('L','M','N');
    AZ p0('a','b','c','d','e');
    {
        boost::iostreams::basic_array_sink<char> sr(buffer, buffer_size);
        boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source(sr);
        boost::archive::binary_oarchive oa(source);
        oa << p0;// <<p1 <<p3;
    }


    XY p10;
    {
        boost::iostreams::basic_array_source<char> sr(buffer, buffer_size);
        boost::iostreams::stream< boost::iostreams::basic_array_source<char> > source(sr);
        boost::archive::binary_iarchive oa(source);
        oa >> p10;
    }
}

int main(int argc, char *argv[])
{
    test_text_archive();
    test_binary_archive();
    test_char_array_archive();

    const int i=100;
    return 0;
}