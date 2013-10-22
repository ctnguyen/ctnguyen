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

	BOOST_CHECK( bad_ramdom <= nb_sample );
}


BOOST_AUTO_TEST_CASE(interger_factorrize)
{
	std::vector<unsigned int> prime_sequence;
	int number = 1;

	//25486 = 2*12743
	int first_sequence[2] = { 2 , 12743 };
	TP1::interger_factorrize( prime_sequence, 25486 );

	BOOST_CHECK( prime_sequence.size() == 2 ); // check if factorize give the good sequence size
	for(int i=0;i<2;++i)
	{
		BOOST_CHECK( prime_sequence[i] == first_sequence[i] ); // check if factorize give the good initial sequence
		number *= prime_sequence[i];
	}
	BOOST_CHECK( number == 25486 ); // check if the product sequence give the initial number
	number=1; //reinitialize the nubmer

	//1928 = 2*2*2*241
	int second_sequence[4] = { 2 , 2 , 2 , 241 };
	TP1::interger_factorrize( prime_sequence, 1928 );

	BOOST_CHECK( prime_sequence.size() == 4 ); // check if factorize give the good sequence size
	for(int i=0;i<4;++i)
	{
		BOOST_CHECK( prime_sequence[i] == second_sequence[i] ); // check if factorize give the good initial sequence
		number *= prime_sequence[i];
	}
	BOOST_CHECK( number == 1928 ); // check if the product sequence give the initial number
	number=1; //reinitialize the nubmer


	//           260467200 =   2*2*2*2*2*2*2*2*2*3*3*5*5*7*17*19
	int third_sequence[16] = { 2,2,2,2,2,2,2,2,2,3,3,5,5,7,17,19 };
	TP1::interger_factorrize( prime_sequence, 260467200 );

	BOOST_CHECK( prime_sequence.size() == 16 ); // check if factorize give the good sequence size
	for(int i=0;i<16;++i)
	{
		BOOST_CHECK( prime_sequence[i] == third_sequence[i] ); // check if factorize give the good initial sequence
		number *= prime_sequence[i];
	}
	BOOST_CHECK( number == 260467200 ); // check if the product sequence give the initial number
	number=1; //reinitialize the nubmer

}


BOOST_AUTO_TEST_CASE(integer_sqrt)
{
	// test randomly 200 time by giving a sqrt, compute is square

	unsigned int nb_sample =200;
	unsigned int min=1;unsigned int max=10000;
	srand (time(NULL));
	int a1 = TP1::uniform(min,max,false);
	for(unsigned int i=0;i<nb_sample;++i)
	{
		unsigned int m_sqrt = TP1::uniform(min,max,false);
		unsigned int i_sqrt = TP1::integer_sqrt( m_sqrt*m_sqrt + m_sqrt );
		BOOST_CHECK(i_sqrt == m_sqrt);
	}

}

BOOST_AUTO_TEST_CASE(newton_sqrt)
{
	double r_number ; double eps = 1e-5;
	double r_sqrt   ; double error= 1000.;

	// 157.259²= 24730.393081
	r_number = 24730.393081 ;
	r_sqrt = TP1::newton_sqrt(r_number,eps);
	error  = r_sqrt - 157.259 ;
	BOOST_CHECK(error < 0.005*157.259  );error= 1000.;

	// 12.58² = 158.2564
	r_number = 158.2564 ;
	r_sqrt = TP1::newton_sqrt(r_number,eps);
	error  = r_sqrt - 12.58 ;
	BOOST_CHECK(error < 0.005*12.58 );error= 1000.;

	// 0.57² = 0.3249
	r_number = 0.3249 ;
	r_sqrt = TP1::newton_sqrt(r_number,eps);
	error  = r_sqrt - 0.57 ;
	BOOST_CHECK(error < 0.005*0.57 );error= 1000.;

}


BOOST_AUTO_TEST_CASE(Point)
{
	{
		TP1::Point m_point(1,3,'A'); BOOST_CHECK(true);
		m_point.affiche();           BOOST_CHECK(true);
		m_point.translate(3,7);      BOOST_CHECK(true);
		m_point.affiche();           BOOST_CHECK(true);
	}

	BOOST_CHECK(true); //test if destructor doesn't break
}


BOOST_AUTO_TEST_SUITE_END()
