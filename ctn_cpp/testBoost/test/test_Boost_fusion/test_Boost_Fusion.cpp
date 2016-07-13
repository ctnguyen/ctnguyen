#define BOOST_TEST_MODULE test_Boost_Fusion
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <cstddef> // NULL
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/fusion/sequence.hpp>
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/include/at_c.hpp>

BOOST_AUTO_TEST_SUITE(All_Types)

BOOST_AUTO_TEST_CASE(default_variant)
{
     boost::fusion::vector<int, char, std::string> stuff;
     int& i = boost::fusion::at_c<0>(stuff); i=100;
     char& ch = boost::fusion::at_c<1>(stuff);
     std::string& str = boost::fusion::at_c<2>(stuff);str="helloworld";
     
}

/// Todo
/// Performance memory binary built files
/// Performance compilation time
/// Performance constructor : default, copy, move
/// Performance assign operator

BOOST_AUTO_TEST_SUITE_END()