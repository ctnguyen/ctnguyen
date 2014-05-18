#include <LMM/instrument/TenorType.h>


template<> const char* Tenor::TYPE_0::NAME = "_Non";template<> const unsigned int Tenor::TYPE_0::NB_MONTH =  0;
template<> const char* Tenor::TYPE_1::NAME =  "_1M";template<> const unsigned int Tenor::TYPE_1::NB_MONTH =  1;
template<> const char* Tenor::TYPE_2::NAME =  "_3M";template<> const unsigned int Tenor::TYPE_2::NB_MONTH =  3;
template<> const char* Tenor::TYPE_3::NAME =  "_6M";template<> const unsigned int Tenor::TYPE_3::NB_MONTH =  6;
template<> const char* Tenor::TYPE_4::NAME =  "_9M";template<> const unsigned int Tenor::TYPE_4::NB_MONTH =  9;
template<> const char* Tenor::TYPE_5::NAME = "_12M";template<> const unsigned int Tenor::TYPE_5::NB_MONTH = 12;
template<> const char* Tenor::TYPE_6::NAME =  "_1Y";template<> const unsigned int Tenor::TYPE_6::NB_MONTH = 12;

const Tenor::TYPE_0 Tenor::_Non;// initialization static variable
const Tenor::TYPE_1 Tenor::_1M;// initialization static variable
const Tenor::TYPE_2 Tenor::_3M;// initialization static variable
const Tenor::TYPE_3 Tenor::_6M;// initialization static variable
const Tenor::TYPE_4 Tenor::_9M;// initialization static variable
const Tenor::TYPE_5 Tenor::_12M;// initialization static variable
const Tenor::TYPE_6 Tenor::_1Y;// initialization static variable


/*
std::map<TenorTypeEnum::TenorTypeEnum, int> TenorType::tenorTypeMap_ = TenorType::create();

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
}*/
