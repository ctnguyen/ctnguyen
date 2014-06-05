#define BOOST_TEST_MODULE LMM_unit_test_helper

#include <boost/test/included/unit_test.hpp>

#include <LMM/helper/LMMTenorStructure.h>


BOOST_AUTO_TEST_SUITE(lmm_test_LMMTenorStructure)

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure_constructor)
{
	Tenor tenorType = Tenor::_3M;
	size_t nbYear = 10;

	LMMTenorStructure lmmTenorStructure(tenorType, nbYear);

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure_comparator)
{
	Tenor tenor1 = Tenor::_3M ; size_t nbYear1 = 2;
	Tenor tenor2 = Tenor::_3M ; size_t nbYear2 = 2;
	Tenor tenor3 = Tenor::_6M ; size_t nbYear3 = 2;
	Tenor tenor4 = Tenor::_3M ; size_t nbYear4 = 4;

	LMMTenorStructure lmmTenorStructure1(tenor1, nbYear1);
	LMMTenorStructure lmmTenorStructure2(tenor2, nbYear2);
	LMMTenorStructure lmmTenorStructure3(tenor3, nbYear3);
	LMMTenorStructure lmmTenorStructure4(tenor4, nbYear4);

	BOOST_CHECK(lmmTenorStructure1 == lmmTenorStructure2);
	BOOST_CHECK(lmmTenorStructure1 != lmmTenorStructure3);
	BOOST_CHECK(lmmTenorStructure1 != lmmTenorStructure4);
}

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure_dates)
{
	Tenor tenor = Tenor::_6M ; size_t tenorInMonth = tenor.convertToMonth();
	size_t nbYear = 2;
	size_t horizonsize = nbYear * (12 / tenorInMonth);

	LMMTenorStructure lmmTenorStructure(tenor, nbYear);

	BOOST_CHECK(lmmTenorStructure.get_horizon() == horizonsize   ) ;
	BOOST_CHECK(lmmTenorStructure.get_nbLIBOR() == horizonsize+1 ) ;

	const std::vector<double>& deltaT = lmmTenorStructure.get_deltaT()    ;
	const std::vector<double>& dates  = lmmTenorStructure.get_tenorDate() ;

	BOOST_CHECK(deltaT.size() == lmmTenorStructure.get_horizon() + 1 );
	BOOST_CHECK( dates.size() == lmmTenorStructure.get_horizon() + 2 );

	BOOST_CHECK(deltaT[0] == 0.5 );
	BOOST_CHECK(deltaT[1] == 0.5 );
	BOOST_CHECK(deltaT[2] == 0.5 );
	BOOST_CHECK(deltaT[3] == 0.5 );
	BOOST_CHECK(deltaT[4] == 0.5 );

	BOOST_CHECK(dates[0] == 0.0 );
	BOOST_CHECK(dates[1] == 0.5 );
	BOOST_CHECK(dates[2] == 1.0 );
	BOOST_CHECK(dates[3] == 1.5 );
	BOOST_CHECK(dates[4] == 2.0 );
	BOOST_CHECK(dates[5] == 2.5 );

	lmmTenorStructure.print("unitTest_LMMTenorStructure.csv");
}

BOOST_AUTO_TEST_SUITE_END()
