#define BOOST_TEST_MODULE interview_test_velocix

#include <boost/test/included/unit_test.hpp>

#include "Helper.h"
#include "Word.h"

#include <ctype.h>
#include <sstream>

BOOST_AUTO_TEST_SUITE(test_Word)

BOOST_AUTO_TEST_CASE(test_reading_sample_text)
{
	
	const char* file_path_name = "sample_text.txt";

	std::ifstream file_stream;
	file_stream.open(file_path_name, std::ios::in);
	
	if (file_stream.is_open())
	{
		Word word;
		while (file_stream.good() )
		{
			file_stream >> word;
			//if (!word.empty()) std::cout << word << std::endl;//ctndebug
		}
	}

	file_stream.close();

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_comparing_word)
{
	std::stringstream ss1,ss2,ss3;
	ss1 << "Hello";
	ss2 << "Hello";
	ss3 << "Word";

	Word word1, word2, word3;
	ss1 >> word1;
	ss2 >> word2;
	ss3 >> word3;
	
	//std::cout <<"word1 " <<word1 << std::endl << "word2 " << word2 << std::endl	<< "word3 " << word3 << std::endl;//ctndebug
	
	BOOST_CHECK(word1 == word2);
	BOOST_CHECK(word1 != word3);
}

BOOST_AUTO_TEST_SUITE_END()
