#define BOOST_TEST_MODULE LMM_unit_test_model
#include <boost/test/included/unit_test.hpp>

#include <LMM/ModelMCLMM/LMMTenorStructure.h>

namespace LMM_unittest
{
LMMTenorStructure get_LMMTenorStrucure_example()
{
	Tenor tenorType = Tenor::_3M;
	size_t horizonYear = 10;

	LMMTenorStructure lmmTenorStructure(tenorType, horizonYear);
	return lmmTenorStructure;
}
}


BOOST_AUTO_TEST_SUITE(lmm_test_model)

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure)
{
	LMMTenorStructure lmmTenorStructure = LMM_unittest::get_LMMTenorStrucure_example();
	lmmTenorStructure.print();

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
