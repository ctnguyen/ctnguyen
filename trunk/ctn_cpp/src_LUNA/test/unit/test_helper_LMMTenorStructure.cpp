#define BOOST_TEST_MODULE LMM_unit_test_helper
#include <boost/test/included/unit_test.hpp>

#include <LMM/helper/LMMTenorStructure.h>

namespace LMM_unittest
{
LMMTenorStructure* get_LMMTenorStrucure_example()
{
	Tenor tenorType = Tenor::_3M;
	size_t horizonYear = 10;

	LMMTenorStructure* lmmTenorStructure= new LMMTenorStructure(tenorType, horizonYear);
	return lmmTenorStructure;
}
}


BOOST_AUTO_TEST_SUITE(lmm_test_LMMTenorStructure)

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure)
{
	LMMTenorStructure* lmmTenorStructure = LMM_unittest::get_LMMTenorStrucure_example();

	lmmTenorStructure->print("test_LMMTenorStructure.csv");

	delete lmmTenorStructure; 
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
