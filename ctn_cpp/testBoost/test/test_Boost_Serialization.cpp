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
//
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>

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

int main(int argc, char *argv[])
{
    TradePoint p;
    std::cout << p <<std::endl;
    std::cout << "Hello World"<<std::endl;

    return 0;
}