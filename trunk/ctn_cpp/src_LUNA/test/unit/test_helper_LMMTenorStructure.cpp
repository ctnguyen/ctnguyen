#define BOOST_TEST_MODULE LMM_unit_test_helper

#include <boost/test/included/unit_test.hpp>

#include <LMM/helper/LMMTenorStructure.h>


BOOST_AUTO_TEST_SUITE(lmm_test_LMMTenorStructure)

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure_constructor)
{
	Tenor tenorType = Tenor::_3M;
	size_t horizonYear = 10;

	LMMTenorStructure lmmTenorStructure(tenorType, horizonYear);
	
	lmmTenorStructure.print("test_LMMTenorStructure.csv");

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
