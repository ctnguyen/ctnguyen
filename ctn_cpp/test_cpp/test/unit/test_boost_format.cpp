/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test_boostformat
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cassert>

#include <boost/format.hpp>

BOOST_AUTO_TEST_SUITE(test_boost_format)

/// see more example for numeric data : https://studiofreya.com/cpp/boost/boostformat-and-wformat-examples-numbers-int-float-double/
/// 

BOOST_AUTO_TEST_CASE(number_formatting)
{
    const double real_number = 123.456789;
    const std::string double_str = (boost::format("%1%") % real_number).str();
    BOOST_CHECK_EQUAL(double_str, "123.457");         // Note number is rounded
    const std::string double_precision_2 = (boost::format("%1$.2f") % real_number).str();
    BOOST_CHECK_EQUAL(double_precision_2, "123.46");  // Note number is rounded
    const std::string fixed_width_double_precision_2 = (boost::format("%1$20.2f") % real_number).str();
    BOOST_CHECK_EQUAL(fixed_width_double_precision_2, "              123.46");

    const int number_int=7;
    const std::string filled_char_fixed_width =  (boost::format("%1%") % boost::io::group(std::setfill('0'), std::setw(3), number_int)).str();  
    BOOST_CHECK_EQUAL(filled_char_fixed_width, "007");
}

BOOST_AUTO_TEST_CASE(test_high_precision_format)
{
    const double very_small_number = 0.000000000123;
    const std::string very_small_number_str = (boost::format("%1%") % very_small_number).str();
    const std::string very_small_number_full_str = (boost::format("%1$.12f") % very_small_number).str();
    BOOST_CHECK_EQUAL(very_small_number_full_str, "0.000000000123");

    const double test_floating_number = 0.0123;
    const std::string test_floating_number_str0 = (boost::format("%1$.0f") % test_floating_number).str();
    const std::string test_floating_number_str1 = (boost::format("%1$.1f") % test_floating_number).str();
    const std::string test_floating_number_str2 = (boost::format("%1$.2f") % test_floating_number).str();
    const std::string test_floating_number_str3 = (boost::format("%1$.3f") % test_floating_number).str();
    const std::string test_floating_number_str4 = (boost::format("%1$.4f") % test_floating_number).str();
    const std::string test_floating_number_str5 = (boost::format("%1$.5f") % test_floating_number).str();
    BOOST_CHECK_EQUAL(test_floating_number_str0, "0");
    BOOST_CHECK_EQUAL(test_floating_number_str1, "0.0");
    BOOST_CHECK_EQUAL(test_floating_number_str2, "0.01");
    BOOST_CHECK_EQUAL(test_floating_number_str3, "0.012");
    BOOST_CHECK_EQUAL(test_floating_number_str4, "0.0123");
    BOOST_CHECK_EQUAL(test_floating_number_str5, "0.01230");
}

BOOST_AUTO_TEST_CASE(example_boost_format)
{
    //using namespace MyNS_ForOutput;
    //using namespace MyNS_Manips;

    std::cout << boost::format("%|1$1| %|2$3|") % "Hello" % 3 << std::endl;

    // Reordering :
    std::cout << boost::format("%1% %2% %3% %2% %1% \n") % "o" % "oo" % "O"; // 'simple' style.
                                                                 //          prints  "o oo O oo o \n"
    std::cout << boost::format("(x,y) = (%1$+5d,%2$+5d) \n") % -23 % 35;     // Posix-Printf style


                                                                 // No reordering :
    std::cout << boost::format("writing %s,  x=%s : %d-th step \n") % "toto" % 40.23 % 50;
    //          prints  "writing toto,  x=40.23 : 50-th step \n"

    std::cout << boost::format("(x,y) = (%+5d,%+5d) \n") % -23 % 35;
    std::cout << boost::format("(x,y) = (%|+5|,%|+5|) \n") % -23 % 35;
    std::cout << boost::format("(x,y) = (%|1$+5|,%|2$+5|) \n") % -23 % 35;
    //   all those are the same,  it prints  "(x,y) = (  -23,  +35) \n"



    // Using manipulators, via 'group' :
    std::cout << boost::format("%2% %1% %2%\n") % 1 % boost::io::group(std::setfill('X'), std::hex, std::setw(4), 16 + 3);
    // prints "XX13 1 XX13\n"


    // printf directives's type-flag can be used to pass formatting options :
    std::cout << boost::format("_%1$4d_ is : _%1$#4x_, _%1$#4o_, and _%1$s_ by default\n") % 18;
    //          prints  "_  18_ is : _0x12_, _ 022_, and _18_ by default\n"

    // Taking the string value :
    std::string s;
    s = boost::str(boost::format(" %d %d ") % 11 % 22);
    assert(s == " 11 22 ");


    // -----------------------------------------------
    //  %% prints '%'

    std::cout << boost::format("%%##%#x ") % 20 << std::endl;
    //          prints  "%##0x14 "


    // -----------------------------------------------
    //    Enforcing the right number of arguments 

    // Too much arguments will throw an exception when feeding the unwanted argument :
    try {
        boost::format(" %1% %1% ") % 101 % 102;
        // the format-string refers to ONE argument, twice. not 2 arguments.
        // thus giving 2 arguments is an error
    }
    catch (boost::io::too_many_args& exc) {
        std::cerr << exc.what() << "\n\t\t***Dont worry, that was planned\n";
    }


    // Too few arguments when requesting the result will also throw an exception :
    try {
        std::cerr << boost::format(" %|3$| ") % 101;
        // even if %1$ and %2$ are not used, you should have given 3 arguments
    }
    catch (boost::io::too_few_args& exc) {
        std::cerr << exc.what() << "\n\t\t***Dont worry, that was planned\n";
    }
}

BOOST_AUTO_TEST_SUITE_END()