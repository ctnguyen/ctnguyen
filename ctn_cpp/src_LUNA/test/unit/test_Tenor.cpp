#define BOOST_TEST_MODULE LMM_unit_test_instrument_Tenor
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <cassert>
#include <string.h>

#include <LMM/instrument/TenorType.h>

BOOST_AUTO_TEST_SUITE(lmm_test_instrument_Tenor)

BOOST_AUTO_TEST_CASE(test_TenorType_constructors)
{

	Tenor TenorNon = Tenor::_Non;
	BOOST_CHECK(TenorNon.nbMonth==0);
	BOOST_CHECK(strcmp(TenorNon.name, "_Non")==0);

	Tenor Tenor1M  = Tenor::_1M;
	BOOST_CHECK( Tenor1M.nbMonth == 1 );
	BOOST_CHECK(strcmp( Tenor1M.name , "_1M" )==0);

	Tenor Tenor3M  = Tenor::_3M;
	BOOST_CHECK( Tenor3M.nbMonth == 3 );
	BOOST_CHECK(strcmp( Tenor3M.name , "_3M" )==0);

	Tenor Tenor6M  = Tenor::_6M;
	BOOST_CHECK( Tenor6M.nbMonth == 6 );
	BOOST_CHECK(strcmp( Tenor6M.name , "_6M" )==0);

	Tenor Tenor9M  = Tenor::_9M;
	BOOST_CHECK( Tenor9M.nbMonth == 9 );
	BOOST_CHECK(strcmp( Tenor9M.name , "_9M" )==0);

	Tenor Tenor12M = Tenor::_12M;
	BOOST_CHECK( Tenor12M.nbMonth == 12 );
	BOOST_CHECK(strcmp( Tenor12M.name , "_12M" )==0);

	Tenor Tenor1Y  = Tenor::_1Y;
	BOOST_CHECK( Tenor1Y.nbMonth == 12 );
	BOOST_CHECK(strcmp( Tenor1Y.name , "_1Y" )==0);
}

BOOST_AUTO_TEST_CASE(test_TenorType_comparing)
{
	Tenor TenorNon1 = Tenor::_Non;
	Tenor TenorNon2 = Tenor::_Non;
	BOOST_CHECK(TenorNon1 == TenorNon2);

	Tenor Tenor12M = Tenor::_12M;
	Tenor Tenor1Y  = Tenor::_1Y;
	BOOST_CHECK(Tenor12M == Tenor1Y);

	BOOST_CHECK(TenorNon1 != Tenor12M);

	BOOST_CHECK( !TenorNon1.isValidTenor() );
	BOOST_CHECK( Tenor12M.isValidTenor() );
}

BOOST_AUTO_TEST_CASE(test_TenorType_calculus)
{
	Tenor Tenor1M  = Tenor::_1M;
	Tenor Tenor3M  = Tenor::_3M;
	Tenor Tenor6M  = Tenor::_6M;
	Tenor Tenor9M  = Tenor::_9M;
	Tenor Tenor12M = Tenor::_12M;
	Tenor Tenor1Y  = Tenor::_1Y;

	BOOST_CHECK(Tenor1Y.convertToMonth()  == 12 );
	BOOST_CHECK(Tenor12M.convertToMonth() == 12 );
	BOOST_CHECK(Tenor6M.convertToMonth()  == 6  );

	BOOST_CHECK(Tenor3M.convertToYear()  == 0.25 );
	BOOST_CHECK(Tenor6M.convertToYear()   == 0.5 );
	BOOST_CHECK(Tenor12M.convertToYear()  == 1.0 );

	BOOST_CHECK(Tenor12M.ratioTo(Tenor1Y)  == 1 );
	BOOST_CHECK(Tenor12M.ratioTo(Tenor9M)  == 1 );
	BOOST_CHECK(Tenor12M.ratioTo(Tenor3M)  == 4 );
	BOOST_CHECK(Tenor12M.ratioTo(Tenor6M)  == 2 );
}

BOOST_AUTO_TEST_SUITE_END()
