#define BOOST_TEST_MODULE M2MO_unit_test_lib_tp1


#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <header_tp1.hpp>

BOOST_AUTO_TEST_SUITE(M2MO_lib_tp1)


BOOST_AUTO_TEST_CASE(test_pgcd_r)
{
	// test several case of trivial GCD
	BOOST_CHECK( TP1::pgcd_r( 7, 5) ==  1 );
	BOOST_CHECK( TP1::pgcd_r(30,12) ==  6 );
	BOOST_CHECK( TP1::pgcd_r(10,30) == 10 );
	BOOST_CHECK( TP1::pgcd_r(28,12) ==  4 );
}


BOOST_AUTO_TEST_SUITE_END()
