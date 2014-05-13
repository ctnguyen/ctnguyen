#include "TenorType.h"

std::map<TenorTypeEnum::TenorTypeEnum, int> TenorType::tenorTypeMap_ = create();

namespace TenorTypeEnum
{
	std::string toString(const TenorTypeEnum& tenorType)
	{
		switch (tenorType)
		{
		case TenorTypeEnum::_Non:
			return "Non";
		case TenorTypeEnum::_1M:
			return "1M";
		case TenorTypeEnum::_3M:
			return "3M";
		case TenorTypeEnum::_6M:
			return "6M";
		case TenorTypeEnum::_12M:
			return "12M";
		case TenorTypeEnum::_1Y:
			return "1Y";
		default:
			throw("Error: not valid TenorType.");
		}
	}

	bool operator==(TenorTypeEnum& tenorType1, TenorTypeEnum& tenorType2)
	{
		switch(tenorType1)
		{
		case TenorTypeEnum::_Non:
			return tenorType2 == TenorTypeEnum::_Non;
		case TenorTypeEnum::_1M:
			return tenorType2 == TenorTypeEnum::_1M;
		case TenorTypeEnum::_3M:
			return tenorType2 == TenorTypeEnum::_3M;
		case TenorTypeEnum::_6M:
			return tenorType2 == TenorTypeEnum::_6M;
		case TenorTypeEnum::_12M:
		case TenorTypeEnum::_1Y:
			return (tenorType2 == TenorTypeEnum::_12M || tenorType2 == TenorTypeEnum::_1Y);
		default:
			throw("Error in TenorTypeEnum, type not define ");
		}
	}

	bool equals(const TenorTypeEnum& a, const TenorTypeEnum& b)
	{
		if(a==b)
			return true;
		else 
			return false;
	}
}