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
	const size_t int_size = sizeof(int);
	BOOST_CHECK(int_size == 4);

	const size_t bitset32_size = sizeof(std::bitset<32>);
	BOOST_CHECK(bitset32_size == 4);

	srand( static_cast<unsigned int>(time(NULL)) );
	const int int_number = rand() % 2000 - 1000 ;
	
	std::string hexastr = helper::convertIntToHexString(int_number);
	int converted_number_hex = helper::convertHexStringToInt(hexastr);
	//std::cout << "x=" << int_number << "	y=" << converted_number_hex << std::endl;
	BOOST_CHECK(int_number == converted_number_hex);

	helper::Binary32 binar = helper::convertIntToBinary(int_number);
	int converted_number_bin = helper::convertBinaryToInt(binar);
	//std::cout << "x=" << int_number << "	y=" << converted_number_bin << std::endl;
	BOOST_CHECK(int_number == converted_number_bin);
}

BOOST_AUTO_TEST_CASE(test_open_file_in_test_data_folder)
{
	/*
	// this programme is in the root directory
	// data file in the subdirectory named exactly "test_data"

	//std::string filepath = "test_data\\task1.txt";
	std::string filepath = "test_data\\task1.bin";
	
	std::ifstream myfile;
	myfile.open( filepath.c_str() );

	const size_t nsize = 10;
	char somewords[nsize];

	myfile.read(somewords, nsize);
	
	std::cout << "File path|" << filepath << std::endl
			  << "First workds|" << somewords << std::endl;

	myfile.close();

	*/
	BOOST_CHECK(true);
}


BOOST_AUTO_TEST_CASE(test_open_bin_file_in_test_data_folder)
{
	// this programme is in the root directory
	// data file in the subdirectory named exactly "test_data"

	/*
	std::string filepath = "test_data\\task1.bin";

	std::ifstream myfile;
	myfile.open(filepath.c_str());

	unsigned int nbLine = 0;
	while ( myfile.good() )
	{
		std::string line;
		getline(myfile , line);

		if (!line.empty() )
		{
			std::cout << "line[" << nbLine << "] " << line << std::endl;
			
			++nbLine;
		}
		else
		{
			std::cout << "line[" << nbLine << "]  =========================== bad line (empty) " <<  std::endl;
		}
	}
	myfile.close();


	BOOST_CHECK(true);
	*/
}

BOOST_AUTO_TEST_SUITE_END()
