#define BOOST_TEST_MODULE interview_test_Maxeler

#include <boost/test/included/unit_test.hpp>
#include <iostream>

#include "VMimage.h"
#include "VMinterpreter.h"

BOOST_AUTO_TEST_SUITE(test_VMinterpreter)

BOOST_AUTO_TEST_CASE(test_VMinterpreter_Constructor)
{
	const std::string file_path_name = "test_data\\test01.bin";
	
	VMimage data;
	try
	{
		data.load(file_path_name.c_str());

		VMinterpreter interpreter(data);

		std::cout << interpreter << std::endl;
	}
	catch (std::string mgs)
	{
		std::cout << mgs << std::endl;
	}

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
