#define BOOST_TEST_MODULE colossus_test__Selection

#include <iostream>
#include <fstream>
#include <ctime>

#include "../DataStream.h"
#include "../Selection.h"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_Selection)



BOOST_AUTO_TEST_CASE(test_constructor)
{
	const char* samlefilename = "sample.txt";
	SampleDataStream datastream(samlefilename);
		
	std::cout << datastream << std::endl;

	Selection(3);
}


BOOST_AUTO_TEST_SUITE_END()
