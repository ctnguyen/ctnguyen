#define BOOST_TEST_MODULE LMM_unit_test_model
#include <boost/test/included/unit_test.hpp>

#include <LMM/ModelMCLMM/LMMTenorStructure.h>

LMMTenorStructure get_LMMTenorStrucure_example()
{
	TenorTypeEnum::TenorTypeEnum tenorType = TenorTypeEnum::TenorTypeEnum::_3M;
	size_t horizonYear = 10;

	LMMTenorStructure lmmTenorStructure(tenorType, horizonYear);
	return lmmTenorStructure;
}



BOOST_AUTO_TEST_SUITE(lmm_test_model)

BOOST_AUTO_TEST_CASE(test_LMMTenorStrucure)
{
	LMMTenorStructure lmmTenorStructure = get_LMMTenorStrucure_example();
	lmmTenorStructure.print();

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()