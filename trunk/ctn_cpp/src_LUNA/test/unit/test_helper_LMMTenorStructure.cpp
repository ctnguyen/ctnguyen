#define BOOST_TEST_MODULE LMM_unit_test_helper

#include <boost/test/included/unit_test.hpp>

#include <LMM/helper/LMMTenorStructure.h>


BOOST_AUTO_TEST_SUITE(lmm_test_LMMTenorStructure)

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure_constructor)
{
	Tenor tenorType = Tenor::_3M;
	size_t horizonYear = 10;

	LMMTenorStructure lmmTenorStructure(tenorType, horizonYear);

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure_comparator)
{
	Tenor tenor1 = Tenor::_3M ; size_t horizonYear1 = 2;
	Tenor tenor2 = Tenor::_3M ; size_t horizonYear2 = 2;
	Tenor tenor3 = Tenor::_6M ; size_t horizonYear3 = 2;
	Tenor tenor4 = Tenor::_3M ; size_t horizonYear4 = 4;

	LMMTenorStructure lmmTenorStructure1(tenor1, horizonYear1);
	LMMTenorStructure lmmTenorStructure2(tenor2, horizonYear2);
	LMMTenorStructure lmmTenorStructure3(tenor3, horizonYear3);
	LMMTenorStructure lmmTenorStructure4(tenor4, horizonYear4);

	BOOST_CHECK(lmmTenorStructure1 == lmmTenorStructure2);
	BOOST_CHECK(lmmTenorStructure1 != lmmTenorStructure3);
	BOOST_CHECK(lmmTenorStructure1 != lmmTenorStructure4);
}

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure_detail)
{
	Tenor tenor = Tenor::_6M ; size_t tenorInMonth = tenor.convertToMonth();
	size_t horizonYear = 2;
	size_t horizonsize = horizonYear * (12 / tenorInMonth);

	LMMTenorStructure lmmTenorStructure(tenor, horizonYear);

	BOOST_CHECK(lmmTenorStructure.get_horizon() == horizonsize);

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

	lmmTenorStructure.print("test_LMMTenorStructure.csv");
}

BOOST_AUTO_TEST_SUITE_END()
