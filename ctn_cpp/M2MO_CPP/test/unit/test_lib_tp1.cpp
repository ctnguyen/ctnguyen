#define BOOST_TEST_MODULE M2MO_unit_test_lib_tp1


#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <cstdlib>
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


BOOST_AUTO_TEST_CASE(test_uniform)
{
	// sample some hundred of time a pair of number
	// if each time the pair of number is the same, that is a bad sampling
	// if the number of bad sampling is too hight, the test will failed
	const int min=0 ; const int max = 100;
	unsigned int nb_sample=200;
	unsigned int bad_ramdom=0;

	srand (time(NULL)); // IMPORTANT reinitialize random seed
	int a1 = TP1::uniform(min,max,false);
	for(unsigned int i=0;i<nb_sample;++i)
	{
		int a2 = TP1::uniform(min,max,false);
		if(a1 == a2) ++bad_ramdom;
		a1=a2;
	}

	BOOST_CHECK( bad_ramdom >= nb_sample );
}



BOOST_AUTO_TEST_SUITE_END()
