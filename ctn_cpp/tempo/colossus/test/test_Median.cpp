#define BOOST_TEST_MODULE colossus_test_Median
#include <iostream>
#include <fstream>
#include <ctime>

#include "DataStream.h"
#include "Median.h"
#include "TrialAnalyzer.h"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_Median)


BOOST_AUTO_TEST_CASE(test_Median1)
{
	const char* samlefilename = "test_SelectionSample3.txt";
	SampleDataStream datastream(samlefilename);

	//std::cout << datastream << std::endl;
		
	Median median;
	TrialAnalyzer tester;

	while (!datastream.isEnd())
	{
		
		datastream.fetchData();
		const std::vector<int>& buffer = datastream.get_DataBuffer();
		
		median.updateData(buffer);
		tester.updateData(buffer);

		//std::cout << "Tester   ]"<< tester << std::endl;
		//std::cout << "Median   ]" << median << std::endl << std::endl;

		const int median_value = median.get_Median();
		const int median_tested = tester.get_Median();

		BOOST_CHECK(median_tested == median_value );
	}
}

BOOST_AUTO_TEST_CASE(test_Median_WithRandomInput)
{
	const size_t nbData = 100;
	SampleDataStream datastream(nbData);

	//std::cout << datastream << std::endl;

	Median median;
	TrialAnalyzer tester;

	while (!datastream.isEnd())
	{

		datastream.fetchData();
		const std::vector<int>& buffer = datastream.get_DataBuffer();

		median.updateData(buffer);
		tester.updateData(buffer);

		//std::cout << "Tester   ]"<< tester << std::endl;
		//std::cout << "Median   ]" << median << std::endl << std::endl;

		const int median_value = median.get_Median();
		const int median_tested = tester.get_Median();

		BOOST_CHECK(median_tested == median_value);
	}
}


BOOST_AUTO_TEST_SUITE_END()
