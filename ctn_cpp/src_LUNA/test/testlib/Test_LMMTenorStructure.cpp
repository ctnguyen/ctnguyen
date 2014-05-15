#include <LMM/ModelMCLMM/LMMTenorStructure.h>

LMMTenorStructure get_LMMTenorStrucure_example()
{
	TenorTypeEnum::TenorTypeEnum tenorType = TenorTypeEnum::TenorTypeEnum::_3M;
	size_t horizonYear = 10;

	LMMTenorStructure lmmTenorStructure(tenorType, horizonYear);
	return lmmTenorStructure;
}

void test_LMMTenorStrucure()
{
	LMMTenorStructure lmmTenorStructure = get_LMMTenorStrucure_example();
	lmmTenorStructure.print();
}