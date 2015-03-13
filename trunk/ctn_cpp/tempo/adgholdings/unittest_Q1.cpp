#define BOOST_TEST_MODULE interview_test_adgholdings

#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <fstream>

#include "Question1.h"
BOOST_AUTO_TEST_SUITE(test_Question1)

BOOST_AUTO_TEST_CASE(test_function_q2)
{
	std::list<char> res;

	Q1::GetMostUsedCharacters("annoying", res);
	Q1::printList(res);

	Q1::GetMostUsedCharacters("implementation", res);
	Q1::printList(res);

}


BOOST_AUTO_TEST_SUITE_END()
