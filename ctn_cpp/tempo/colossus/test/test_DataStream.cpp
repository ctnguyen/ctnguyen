#define BOOST_TEST_MODULE LMM_test_lib

#include <iostream>

#include "../DataStream.h"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_DataStream)

BOOST_AUTO_TEST_CASE(test_constructor_file_read)
{
	const char* filename = "sample.txt";
	SampleDataStream datastream(filename);

	std::cout << datastream << std::endl;	
	BOOST_CHECK(true);
}

/*
BOOST_AUTO_TEST_CASE(test_constructor_random_generator)
{
	SampleDataStream datastream(10);

	std::cout << datastream << std::endl;

	BOOST_CHECK(true);
}
*/
BOOST_AUTO_TEST_SUITE_END()
