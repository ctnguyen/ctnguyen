#define BOOST_TEST_MODULE M2MO_unit_test_lib_tp2


#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <header_tp2.hpp>

BOOST_AUTO_TEST_SUITE(M2MO_lib_tp2)


BOOST_AUTO_TEST_CASE(test_adress)
{
	int* p = new int;
	TP2::adress(p);
	delete p;
	BOOST_CHECK( true );
}


BOOST_AUTO_TEST_SUITE_END()
