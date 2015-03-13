#define BOOST_TEST_MODULE interview_test_adgholdings

#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <fstream>

#include "Question2.h"
BOOST_AUTO_TEST_SUITE(test_Question2)


BOOST_AUTO_TEST_CASE(test_first_test)
{
	int m_array[Q2::MAX_NUMBER];

	Q2::RandomlyInitialize(m_array);
	//Q2::PrintArray(m_array);//ctndebug
	//std::cout << std::endl << std::endl;//ctndebug
	const int dropped_value = Q2::RandomlyDropOneElement(m_array);
	//Q2::PrintArray(m_array);//ctndebug

	const int found_missing_value = Q2::GetNumberMissing(m_array);
	
	//std::cout << "Dropped Value="<<dropped_value<<"		found value="<<found_missing_value << std::endl;//ctndebug
	
	//BOOST_CHECK(dropped_value == found_missing_value);
}

BOOST_AUTO_TEST_SUITE_END()
