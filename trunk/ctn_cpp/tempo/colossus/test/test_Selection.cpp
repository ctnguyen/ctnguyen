#define BOOST_TEST_MODULE colossus_test_Selection

#include <iostream>
#include <fstream>
#include <ctime>

#include "DataStream.h"
#include "Selection.h"
#include "TrialAnalyzer.h"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_Selection)



BOOST_AUTO_TEST_CASE(test_Selection_Buffer1)
{
	const unsigned int k = 3;
	const char* samlefilename = "test_SelectionSample3.txt";
	SampleDataStream datastream(samlefilename);
		
	std::cout << datastream << std::endl;

	Selection selection(k);
	TrialAnalyzer tester;

	while (!datastream.isEnd())
	{
		datastream.fetchData();
		const std::vector<int>& buffer = datastream.get_DataBuffer();
		
		selection.updateData(buffer);
		tester.updateData(buffer);
		
		//std::cout <<"tester memory " << tester << std::endl;
		//std::cout <<"Selection " << selection << std::endl;
		
		const int k_selection = selection.get_OrderStatistic(k);
		const int k_tested = tester.get_OrderStatistic(k);
		BOOST_CHECK( k_selection == k_tested );
	}
}


BOOST_AUTO_TEST_SUITE_END()
