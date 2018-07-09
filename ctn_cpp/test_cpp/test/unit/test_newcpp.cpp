/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test_newcpp
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <vector>
#include <array>

BOOST_AUTO_TEST_SUITE(test_all_newcpp)

struct EmptyStruct{};
BOOST_AUTO_TEST_CASE(test_size_of)
{
    const size_t size_of_bool = sizeof(bool);
    const size_t size_of_char = sizeof(char);
    const size_t size_of_empt = sizeof(EmptyStruct);
    
    BOOST_TEST(size_of_bool, size_of_char);
    BOOST_TEST(size_of_empt, size_of_char);
    
    const size_t nbElem=10;
    std::vector<bool> boolvect3;
    std::vector<bool> boolvect4;
    for(size_t i=0;i<nbElem;++i)
        boolvect3.push_back(i%2==0);
    for(size_t i=0;i<nbElem+1;++i)
        boolvect4.push_back(!(i%2==0));
    std::vector<bool> boolvect1{true};
    std::vector<bool> boolvect2{true,false};
    std::vector<bool> boolvect{true,true,false,false,true,false,true,false};
    const size_t size_of_boolvect1 = sizeof boolvect1;//?
    const size_t size_of_boolvect2 = sizeof boolvect2;//?
    const size_t size_of_boolvect3 = sizeof boolvect3;//?
    const size_t size_of_boolvect4 = sizeof boolvect4;//?
    const size_t size_of_boolvect = sizeof(boolvect);//?
    const size_t size_of_boolvecttype = sizeof(std::vector<bool>);
    const size_t size_of_emptvect = sizeof(std::vector<EmptyStruct>);//?

    const size_t size_of_array = sizeof(std::array<bool,10>);
}

BOOST_AUTO_TEST_SUITE_END()