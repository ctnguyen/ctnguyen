#define BOOST_TEST_MODULE interview_test_Maxeler

#include <boost/test/included/unit_test.hpp>
#include <iostream>

#include "VMimage.h"

BOOST_AUTO_TEST_SUITE(test_VMimage)

BOOST_AUTO_TEST_CASE(test_VMimage_Constructor)
{
	VMimage object;

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
