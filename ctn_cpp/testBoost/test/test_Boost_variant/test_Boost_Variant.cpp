#define BOOST_TEST_MODULE test_Boost_Variant
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <cstddef> // NULL
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/variant.hpp>

BOOST_AUTO_TEST_SUITE(All_Types)


BOOST_AUTO_TEST_CASE(default_variant)
{
     boost::variant< int, std::string > u("hello world");
     u=1;
     std::cout << u; // output: hello world

    const int i=boost::get<int>(u);
    //const std::string strval = boost::get<std::string>(u);
    const int ii=i;
    BOOST_CHECK(true);
}

/// Todo test performance
//http://stackoverflow.com/questions/11906741/boost-variant-vs-virtual-interface-performance
/// Performance memory binary built files
/// Performance compilation time
/// Performance constructor : default, copy, move
/// Performance assign operator

BOOST_AUTO_TEST_SUITE_END()