#define BOOST_TEST_MODULE LMM_unit_test_model
#include <boost/test/included/unit_test.hpp>

#include <LMM/ModelMCLMM/HGVolatilityFunction.h>

BOOST_AUTO_TEST_SUITE(lmm_test_volatility)

HGVolatilityFunction get_VolatilityFunction_example()
{
	TenorTypeEnum::TenorTypeEnum tenorType = TenorTypeEnum::TenorTypeEnum::_3M;
	size_t horizonYear = 10;

	LMMTenorStructure lmmTenorStructure(tenorType, horizonYear);

	double a = -0.06;
	double b = 0.17;
	double c = 0.54;
	double d = 0.17;
	AbcdParams abcdParams(a,b,c,d);
	AbcdPWConstFunction abcdPWConstFunction(abcdParams, lmmTenorStructure);

	HGVolatilityFunction hgVolatilityFunction (abcdParams,  lmmTenorStructure); 
	return hgVolatilityFunction;
}

BOOST_AUTO_TEST_CASE(test_VolatilityFunction)
{
	//HGVolatilityFunction hgVolatilityFunction = get_VolatilityFunction_example();
	//hgVolatilityFunction.print();

	BOOST_CHECK(true);
}


BOOST_AUTO_TEST_SUITE_END()