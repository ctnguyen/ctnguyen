#define BOOST_TEST_MODULE interview_test_Maxeler

#include <boost/test/included/unit_test.hpp>
#include <iostream>

#include "VMimage.h"

BOOST_AUTO_TEST_SUITE(test_VMimage)

BOOST_AUTO_TEST_CASE(test_VMimage_Constructor)
{
	VMimage data;
	const std::string file_path_name = "test_data\\test01.bin";
	//const std::string file_path_name = "test_data\\te";

	try
	{
		data.load(file_path_name.c_str());

		for (size_t i = 0; i < (size_t)data.size(); ++i)
		{
			std::cout << data[i] << std::endl;
		}
	}
	catch (std::string mgs)
	{
		std::cout << mgs << std::endl;
	}
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
