#pragma once
#ifndef TENOR_TYPE_H
#define TENOR_TYPE_H

#include <map>
#include <string>
#include <cassert>

//! TODO: understand why it is like this ! 
//! shit rubish VS, 2h pour rien, shit merde compilateur ! 

//
//namespace TenorTypeEnum// problem of enum
//{
//
//	enum TenorTypeEnum {_Non, _1M, _3M, _6M, _12M, _1Y};
//	std::string toString(const TenorTypeEnum& tenorType);
//	bool equals(TenorTypeEnum a, TenorTypeEnum b);
//}

//http://stackoverflow.com/questions/15451382/implementation-of-operators-for-enum-class
namespace TenorTypeEnum //TODO rewrite in a clean way
{
	enum class TenorTypeEnum
	{
		_Non, _1M, _3M, _6M, _12M, _1Y
	};

	bool operator==(TenorTypeEnum& tenorType1, TenorTypeEnum& tenorType2); // TODO rewrite this isEqual
	std::string toString(const TenorTypeEnum& tenorType);
}


class TenorType
{	
public:
	//! YY TODO: compile  Error 
	static std::map<TenorTypeEnum::TenorTypeEnum, int> tenorTypeMap_;
	static std::map<TenorTypeEnum::TenorTypeEnum, int> create()
	{
		std::map<TenorTypeEnum::TenorTypeEnum, int> m;
		m[TenorTypeEnum::TenorTypeEnum::_Non] = -1;  // not used.
		m[TenorTypeEnum::TenorTypeEnum::_1M]  = 1;   // when tenorType: a>b, a%b = 0. 
		m[TenorTypeEnum::TenorTypeEnum::_3M]  = 3;  
		m[TenorTypeEnum::TenorTypeEnum::_6M]  = 6;  
		m[TenorTypeEnum::TenorTypeEnum::_12M] = 12;  
		m[TenorTypeEnum::TenorTypeEnum::_1Y]  = 12;  
		return m; 
	}

public:
	static bool isValidTenorType(const TenorTypeEnum::TenorTypeEnum& tenorType) 
	{
		std::map<TenorTypeEnum::TenorTypeEnum, int>::const_iterator itr = tenorTypeMap_.find(tenorType);
		if(itr !=tenorTypeMap_.end() && itr->first != TenorTypeEnum::TenorTypeEnum::_Non)
			return true;
		else
			return false;
	}

	static double convertToYear(const TenorTypeEnum::TenorTypeEnum& tenorType) 
	{
		assert(isValidTenorType(tenorType));
		return tenorTypeMap_.at(tenorType)/12.0;
	}

	static size_t convertToMonth(const TenorTypeEnum::TenorTypeEnum& tenorType)
	{
		assert(isValidTenorType(tenorType));
		return tenorTypeMap_.at(tenorType);
	}

	//! if (tenorType1>tenorType2) reutrn tenorType1/tenorType2;
	//! else throw
	static size_t TenorTypeRatio(const TenorTypeEnum::TenorTypeEnum& tenorType1,
								 const TenorTypeEnum::TenorTypeEnum& tenorType2) 
	{
		assert(isValidTenorType(tenorType1) && isValidTenorType(tenorType2) && convertToMonth(tenorType1) >= convertToMonth(tenorType2));

		size_t tenorTypeValue1 = convertToMonth(tenorType1);  // have to use at(...), because [] operator is not const.
 		size_t tenorTypeValue2 = convertToMonth(tenorType2);

		return tenorTypeValue1/tenorTypeValue2;  
	}

	//! this private part is to ensure that TenorType class IS NOT to be instantiated
private :
	TenorType(){}
	TenorType(TenorType const& );
	void operator=(TenorType const& );
};


#endif /* TENOR_TYPE_H */