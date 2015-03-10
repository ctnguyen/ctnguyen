#define BOOST_TEST_MODULE interview_test_velocix

#include <boost/test/included/unit_test.hpp>


#include <iostream>

#include "Helper.h"
#include "TextProcess.h"

BOOST_AUTO_TEST_SUITE(test_TextProcess)

BOOST_AUTO_TEST_CASE(test_simple_stream_processing)
{
	TextProcess textprocess;

	std::stringstream ss; ss << "hello Velocix, I am a test hello am hello Velocix";

	unsigned int nbWord=0;
	Word word;
	while (!ss.eof())
	{
		ss >> word;
		if (!word.empty()) // IMPORTANT TO CHECK IF word is not empty before any use
		{
			++nbWord; //std::cout << word << std::endl;//ctndebug
			textprocess.add_Word(word);
		}
	}

	Result res;
	textprocess.get_Result(res);

	//std::cout << textprocess << std::endl;//ctndebug
	//std::cout << res << std::endl;//ctndebug	

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_text_file_processing)
{
	//const char* file_path_name = "sample_text.txt"; // 92 words, time very small
	const char* file_path_name = "referece_text.txt";// 19073 words, reading time 15s

	std::ifstream file_stream;
	file_stream.open(file_path_name, std::ios::in);

	if (file_stream.is_open())
	{
		Word word;
		TextProcess textprocess;
		unsigned int nbWord = 0;

		clock_t start_reading = std::clock();
		while (file_stream.good())
		{
			file_stream >> word;
			if (!word.empty())
			{
				++nbWord; //if (!word.empty()) std::cout << word << std::endl;//ctndebug
				textprocess.add_Word(word);
			}
		}
		clock_t end_reading = std::clock();
		double reading_time = double(end_reading - start_reading) / CLOCKS_PER_SEC;
		
		Result res;
		clock_t start_res = std::clock();
		textprocess.get_Result(res);
		clock_t end_res = std::clock();
		double res_time = double(end_reading - start_reading) / CLOCKS_PER_SEC;

		//std::cout << textprocess << std::endl;//ctndebug
		std::cout << res << std::endl;//ctndebug
		std::cout << "Number word=" << nbWord << "	reading time=" << reading_time <<"	result_time"<<res_time<< std::endl;//ctndebug	
	}

	file_stream.close();

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
