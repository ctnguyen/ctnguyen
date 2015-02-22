#define BOOST_TEST_MODULE colossus_test_Selection

#include <iostream>
#include <fstream>
#include <ctime>

#include "DataStream.h"
#include "Selection.h"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_Selection)



BOOST_AUTO_TEST_CASE(test_Selection_Buffer1)
{
	const char* samlefilename = "test_SelectionSample3.txt";
	SampleDataStream datastream(samlefilename);
		
	std::cout << datastream << std::endl;

	Selection selection(3);

	while (!datastream.isEnd())
	{
		datastream.update();
		const std::vector<int>& buffer = datastream.get_DataBuffer();
		
		selection.fetchData(buffer);
		std::cout << selection << std::endl;
	}
}


BOOST_AUTO_TEST_SUITE_END()
