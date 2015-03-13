#define BOOST_TEST_MODULE interview_test_adgholdings

#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <fstream>

#include "Question4.h"
BOOST_AUTO_TEST_SUITE(test_Question4)


BOOST_AUTO_TEST_CASE(test_first_test)
{
	int sum;
	std::list<int> res;

	Q4::GetMaxSum(sum, res);
	std::cout << "Sum=" << sum << std::endl;
	Q4::printList(res);

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
