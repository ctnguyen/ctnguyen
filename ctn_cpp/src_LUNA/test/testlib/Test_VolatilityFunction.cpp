//#include <LMM/ModelMCLMM/LMMTenorStructure.h>
#include <LMM/ModelMCLMM/HGVolatilityFunction.h>

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

void test_VolatilityFunction()
{
	HGVolatilityFunction hgVolatilityFunction = get_VolatilityFunction_example();
	hgVolatilityFunction.print();

}