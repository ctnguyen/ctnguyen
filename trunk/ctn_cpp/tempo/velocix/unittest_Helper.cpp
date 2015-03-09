#define BOOST_TEST_MODULE interview_test_velocix

#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <fstream>

#include "Helper.h"


BOOST_AUTO_TEST_SUITE(test_Helper)

BOOST_AUTO_TEST_CASE(test_read_text_file)
{
	const int arraysize = 100000;

	char myArray[arraysize];
	//char current_char;
	int num_characters = 0;
	int i = 0;

	const char* file_path_name = "sample_text.txt";

	std::ifstream file_stream;
	file_stream.open(file_path_name, std::ios::in);
	
	if (file_stream.is_open())
	{
		while (!file_stream.eof())
		{
			file_stream >> myArray[i];
			i++;
			num_characters++;
		}

		for (int i = 0; i <= num_characters; i++)
		{

			std::cout << myArray[i] << std::endl;
		}
	}


	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
