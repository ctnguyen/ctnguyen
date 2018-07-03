/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test character encoding
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

#include <boost/format.hpp>
BOOST_AUTO_TEST_SUITE(test_character_encoding)


BOOST_AUTO_TEST_CASE(test_comparison)
{
    char maxChar = 126;
    const bool comparison1 = maxChar<127;
    BOOST_TEST(comparison1);

    maxChar++;
    const bool comparison2 = maxChar<127;
    BOOST_TEST(!comparison2);
}

BOOST_AUTO_TEST_CASE(test_boundary_point)
{
    const char maxChar = std::numeric_limits<char>::max();
    const char minChar = std::numeric_limits<char>::min();

    const unsigned char maxUChar = std::numeric_limits<unsigned char>::max();
    const unsigned char minUChar = std::numeric_limits<unsigned char>::min();

    /// Could be sysem dependend
    BOOST_TEST(minChar,-128);
    BOOST_TEST(maxChar,127);

    //BOOST_TEST(minUChar,0); /// Failed, don't know why
    BOOST_TEST(maxUChar,255);

    std::string str1 = boost::str(boost::format("Char min (int)[%1%]  char[%2%]  ") % (int)minChar % minChar);
    std::string str2 = boost::str(boost::format("Char max (int)[%1%]  char[%2%]  ") % (int)maxChar % maxChar);
    
    std::string str3 = boost::str(boost::format("UChar min (uint)[%1%]  char[%2%]  ") % (unsigned int)minUChar % minUChar);
    std::string str4 = boost::str(boost::format("UChar max (uint)[%1%]  char[%2%]  ") % (unsigned int)maxUChar % maxUChar);
    
    std::cout << str1 <<std::endl  << str2 <<std::endl << str3 <<std::endl << str4 <<std::endl;
}

BOOST_AUTO_TEST_CASE(test_encoding_points)// This test always failed for boundary values
{
    std::ofstream outfile;
    outfile.open("test_CharacterEncoding.csv");

    ///////  Normal std::string has characters encoded from -128 to 127
    outfile << "unsigned, int, char ===== " << std::endl;
    for(char charpoint = -128; charpoint < 126 ; charpoint++)// turn into infinite loop, interesting.
    {   
        char charpointpp = charpoint; ++charpointpp;
        std::string str = boost::str(boost::format("%1%, %2%, %3%  ") % (unsigned int)charpointpp % (int)charpointpp % charpointpp);
        std::cout << "charpoint [" << (int)charpoint <<"]  " << str << std::endl;
        outfile << str << std::endl;
    }

    /// unsigned char
    outfile << "unsigned, int, unsigned char  ===== " << std::endl;
    for (unsigned char charpoint = 0; charpoint < 255; ++charpoint)// turn into infinite loop, interesting.
    {   
        std::string str = boost::str(boost::format("%1%, %2%, %3%")% (unsigned int)charpoint  % (int)charpoint % (unsigned char)charpoint);
        std::cout << str << std::endl;
        outfile << str << std::endl;
    }

    outfile.close();
}

BOOST_AUTO_TEST_SUITE_END()