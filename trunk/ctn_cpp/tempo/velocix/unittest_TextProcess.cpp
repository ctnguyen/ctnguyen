#define BOOST_TEST_MODULE interview_test_velocix

#include <boost/test/included/unit_test.hpp>


#include <iostream>

#include "Helper.h"
#include "TextProcess.h"

BOOST_AUTO_TEST_SUITE(test_TextProcess)

BOOST_AUTO_TEST_CASE(test_simple_stream_processing)
{
	TextProcess textprocess;

	std::stringstream ss; ss << "hello Velocix, I am a test";

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

	std::cout << textprocess << std::endl;

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
