#define BOOST_TEST_MODULE interview_test_velocix

#include <boost/test/included/unit_test.hpp>

#include "Helper.h"
#include "Word.h"

#include <ctype.h>

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
			if (!word.empty())
				std::cout << word << std::endl;
		}
	}

	file_stream.close();

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
