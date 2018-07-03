/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test_boost_random
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

BOOST_AUTO_TEST_SUITE(all_random)


BOOST_AUTO_TEST_CASE(random_string)
{
	/*<< We first define the characters that we're going
	to allow.  This is pretty much just the characters
	on a standard keyboard.
	>>*/
	std::string chars(
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"1234567890"
		"!@#$%^&*()"
		"`~-_=+[{]{\\|;:'\",<.>/? ");
	/*<< We use __random_device as a source of entropy, since we want
	passwords that are not predictable.
	>>*/
	boost::random::random_device rng;
	/*<< Finally we select 8 random characters from the
	string and print them to cout.
	>>*/
	boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
	for (int i = 0; i < 8; ++i) {
		std::cout << chars[index_dist(rng)];
	}
	std::cout << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()