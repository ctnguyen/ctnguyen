#define BOOST_TEST_MODULE colossus_test_DataStream

#include <iostream>
#include <fstream>
#include <ctime>

#include "helper.h"
#include "DataStream.h"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_DataStream)

const unsigned int N = 10;
const char* samlefilename = "sample.txt";


BOOST_AUTO_TEST_CASE(test_constructor_random_generator)
{
	SampleDataStream datastream(N);
		
	std::ifstream infile(samlefilename);
	if (!infile.good())
	{
		std::ofstream sampleFile;
		sampleFile.open(samlefilename);
		
		time_t t = time(0); struct tm * now = localtime(&t) ;
		sampleFile<<"# Data sample generated " << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-'	<< now->tm_mday	<< std::endl;
		
		sampleFile << datastream;
		sampleFile.close();
	}
	else
	{
		std::cout << " Sample File is not rewrite" << std::endl;
	}
	
	const std::vector<int>& offlinedata = datastream.get_OfflineData();
	BOOST_CHECK(offlinedata.size() == N);
	//std::cout << datastream << std::endl;	
}

BOOST_AUTO_TEST_CASE(test_constructor_file_read)
{
	// small bug when a line have non number (at the end of file where a new line charactere
	
	SampleDataStream datastream(samlefilename);

	const std::vector<int>& offlinedata = datastream.get_OfflineData();
	BOOST_CHECK(offlinedata.size() == N);

	//std::cout << datastream << std::endl;
}

BOOST_AUTO_TEST_CASE(test_data_processing)
{
	SampleDataStream datastream(N);
	
	unsigned int nbProcess = 0;

	std::vector<int> container;

	while(!datastream.isEnd())
	{
		datastream.fetchData();
		const std::vector<int>& buffer = datastream.get_DataBuffer();
		container.push_back(buffer[0]);
	}

	const std::vector<int>& offlinedata = datastream.get_OfflineData();

	BOOST_CHECK( offlinedata.size() == container.size() );
	for (size_t i = 0; i < N; ++i)
	{
		BOOST_CHECK(offlinedata[i] == container[i]);
	}

	//std::cout << datastream << std::endl;
}

BOOST_AUTO_TEST_CASE(test_FileStreamReader)
{
	SampleDataStream datastream(samlefilename);

	const std::vector<int>& offline_data1 = datastream.get_OfflineData();
	std::vector<int> offline_data2;

	FileStreamReader file_reader(samlefilename);
	while (!file_reader.isEnd())
	{
		file_reader.fetchData();
		const std::vector<int>& buffer = file_reader.get_DataBuffer();
		offline_data2.insert(offline_data2.end(),buffer.begin(), buffer.end());
	}

	//std::cout << "offline1 " << offline_data1 << std::endl;
	//std::cout << "offline2 " << offline_data2 << std::endl;
	
	BOOST_CHECK(offline_data1.size() == offline_data2.size());
	for (size_t i = 0; i < offline_data1.size(); ++i)
	{
		BOOST_CHECK(offline_data1[i] == offline_data2[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END()
