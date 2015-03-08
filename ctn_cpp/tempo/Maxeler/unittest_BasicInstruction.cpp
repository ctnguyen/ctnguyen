#define BOOST_TEST_MODULE interview_test_Maxeler

#include <boost/test/included/unit_test.hpp>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <ctime>
#include <cstdlib>

#include "Helper.h"

BOOST_AUTO_TEST_SUITE(test_BasicInstructions)

BOOST_AUTO_TEST_CASE(test_number_conversion)
{
	// test conversion between 
	// integer, hexa, binary (bit set 32)
	const size_t int_size = sizeof(helper::Int32);
	BOOST_CHECK(int_size == 4);

	const size_t bitset32_size = sizeof(std::bitset<32>);
	BOOST_CHECK(bitset32_size == 4);

	srand( static_cast<unsigned int>(time(NULL)) );
	const helper::Int32 int_number = rand() % 2000 - 1000;
	
	std::string hexastr = helper::convertInt32ToHexString(int_number);
	helper::Int32 converted_number_hex = helper::convertHexStringToInt32(hexastr);
	//std::cout << "x=" << int_number << "	y=" << converted_number_hex << std::endl;
	BOOST_CHECK(int_number == converted_number_hex);

	helper::Binary32 binar = helper::convertInt32ToBinary32(int_number);
	helper::Int32 converted_number_bin = helper::convertBinary32ToInt32(binar);
	//std::cout << "x=" << int_number << "	y=" << converted_number_bin << std::endl;
	BOOST_CHECK(int_number == converted_number_bin);
}

BOOST_AUTO_TEST_CASE(test_open_bin_file_in_test_data_folder)
{
	// check if every *.bin files are good

	std::vector<std::string> file_list
	{
		"task1.bin","task2.bin","test01.bin","test02.bin","test03.bin","test04.bin","test05.bin","test06.bin",
		"test07.bin","test08.bin","test09.bin","test10.bin","test11.bin","test12.bin","test13.bin","test14.bin",
		"test15.bin","test16.bin","test17.bin","test18.bin","test19.bin","test20.bin","test21.bin","test22.bin",
		"test23.bin","test24.bin","test25.bin"
	};

	for (size_t i = 0; i < file_list.size();++i)
	{
		const std::string file_path_name = "test_data\\" + file_list[i];

		std::ifstream file_stream;
		file_stream.open(file_path_name.c_str());

		unsigned int nbLine = 0;
		unsigned int nbEmptyLine = 0;

		while (file_stream.good())
		{
			std::string line;
			getline(file_stream, line);

			if (!line.empty())
			{
				++nbLine;
			}
			else
			{
				//std::cout << "line[" << nbLine << "]  =========================== bad line (empty) " << std::endl;
				++nbEmptyLine;
			}
		}
		file_stream.close();

		BOOST_CHECK(nbLine > 0); // file should not be empty
		BOOST_CHECK(nbEmptyLine <2 ); // only at most one line at the end of the file can be empty
	}
}

BOOST_AUTO_TEST_CASE(test_open_file_in_test_data_folder)
{
	/*
	// this programme is in the root directory
	// data file in the subdirectory named exactly "test_data"

	std::string filepath = "test_data\\task1.bin";

	*/
	BOOST_CHECK(true);
}


BOOST_AUTO_TEST_SUITE_END()
