#define BOOST_TEST_MODULE interview_test_velocix

#include <boost/test/included/unit_test.hpp>


#include <iostream>

#include "Helper.h"
#include "TextProcess.h"

BOOST_AUTO_TEST_SUITE(test_TextProcess)

BOOST_AUTO_TEST_CASE(test_constructor)
{
	TextProcess textprocess;
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
