#define BOOST_TEST_MODULE interview_test_MyClass

#include <boost/test/included/unit_test.hpp>
#include <iostream>

#include "MyClass.h"

BOOST_AUTO_TEST_SUITE(test_MyClass)

BOOST_AUTO_TEST_CASE(test_MyClass_Constructor)
{
	MyClass object;

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
