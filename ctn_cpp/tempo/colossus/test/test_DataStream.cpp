#define BOOST_TEST_MODULE LMM_test_lib

#include "../DataStream.h"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_DataStream)

BOOST_AUTO_TEST_CASE(test_constructor)
{
	DataStream datastream;

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
