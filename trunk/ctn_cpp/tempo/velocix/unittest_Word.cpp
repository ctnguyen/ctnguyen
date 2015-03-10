#define BOOST_TEST_MODULE interview_test_velocix

#include <boost/test/included/unit_test.hpp>

#include "Helper.h"
#include "Word.h"

#include <cctype>
#include <ctime>
#include <sstream>

BOOST_AUTO_TEST_SUITE(test_Word)

BOOST_AUTO_TEST_CASE(test_reading_stringstream)
{
	std::stringstream ss; ss << "hello Velocix, I am a test";

	unsigned int nbWord=0;
	Word word;
	while (!ss.eof())
	{
		ss >> word;
		if (!word.empty()) // IMPORTANT TO CHECK IF word is not empty before any use
		{
			++nbWord; //std::cout << word << std::endl;//ctndebug
		}
	}

	BOOST_CHECK(nbWord==6);
}

BOOST_AUTO_TEST_CASE(test_reading_sample_text)
{
	
	//const char* file_path_name = "sample_text.txt";
	const char* file_path_name = "referece_text.txt";

	std::ifstream file_stream;
	file_stream.open(file_path_name, std::ios::in);
	
	if (file_stream.is_open())
	{
		clock_t start_reading = std::clock();
		Word word;
		unsigned int nbWord=0;
		while (file_stream.good() )
		{
			file_stream >> word;
			if (!word.empty())
			{
				++nbWord; //if (!word.empty()) std::cout << word << std::endl;//ctndebug
			}
		}
		clock_t end_reading = std::clock();
		double reading_time = double(end_reading - start_reading) / CLOCKS_PER_SEC;
		std::cout << "Number word="<<nbWord << "	time="<<reading_time<< std::endl;//ctndebug
	}

	file_stream.close();

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_comparing_word)
{
	std::stringstream ss1,ss2,ss3;
	ss1 << "Hello";
	ss2 << "Hello";
	ss3 << "World";

	Word word1, word2, word3;
	ss1 >> word1;
	ss2 >> word2;
	ss3 >> word3;
	
	//std::cout <<"word1 " <<word1 << std::endl << "word2 " << word2 << std::endl	<< "word3 " << word3 << std::endl;//ctndebug
	
	BOOST_CHECK(word1 == word2);
	BOOST_CHECK(word1 != word3);
}

BOOST_AUTO_TEST_CASE(test_copy_word)
{
	std::stringstream ss1, ss2;
	ss1 << "Hello";
	ss2 << "World";
	
	Word word1; ss1 >> word1;
	
	Word word2(word1);
	BOOST_CHECK(word1 == word2);
	//std::cout << "word1 " << word1 << std::endl << "word2 " << word2 << std::endl;//ctndebug

	Word word3;
	ss2 >> word1;
	word3 = word1;
	//std::cout << "word1 " << word1 << std::endl << "word2 " << word2 << std::endl << "word3 " << word3 << std::endl;//ctndebug
	BOOST_CHECK(word3 == word1);
	BOOST_CHECK(word3 != word2);
}

BOOST_AUTO_TEST_SUITE_END()
