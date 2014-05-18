#ifndef TENOR_TYPE_H
#define TENOR_TYPE_H
#pragma once


#include <map>
#include <string>
#include <cassert>

/*! To factorize, the class 'Tenor' will replace the 'TenorTypeEnum::TenorTypeEnum'
 *
 */
class Tenor
{
public:

	/*! To define a new TenorType, user has to define
	 * - TYPEID   of tenor type
	 * - NAME     of tenor type
	 * - NB_MONTH number of month of tenor type
	 * by specializing this template
	 */
	template<unsigned int TYPEID> class TenorType
	{
	public :
		static const char*        NAME     ;
		static const unsigned int NB_MONTH ;

		TenorType(){}
	};

	static const TenorType<0>  _Non;typedef TenorType<0> TYPE_0;
	static const TenorType<1>   _1M;typedef TenorType<1> TYPE_1;
	static const TenorType<2>   _3M;typedef TenorType<2> TYPE_2;
	static const TenorType<3>   _6M;typedef TenorType<3> TYPE_3;
	static const TenorType<4>   _9M;typedef TenorType<4> TYPE_4;
	static const TenorType<5>  _12M;typedef TenorType<5> TYPE_5;
	static const TenorType<6>   _1Y;typedef TenorType<6> TYPE_6;


	//! Constructor build a tenor by giving its type
	template<unsigned int NBMONTH>
	Tenor(const TenorType<NBMONTH>&):name(TenorType<NBMONTH>::NAME),nbMonth(TenorType<NBMONTH>::NB_MONTH){}

	//! check if two tenor is equal
	bool operator==(const Tenor& other) const { return (nbMonth == other.nbMonth); }
	bool operator!=(const Tenor& other) const { return (nbMonth != other.nbMonth); }

	bool isValidTenor()     const { return nbMonth>0;    }

	double convertToYear()  const { assert( this->isValidTenor() ); return nbMonth/12.0;}
	size_t convertToMonth() const { assert( this->isValidTenor() ); return nbMonth;}

	size_t ratioTo(const Tenor& other) const
	{
		assert( this->isValidTenor() );assert( other.isValidTenor() );

		size_t nb_month1 = this->convertToMonth();
 		size_t nb_month2 = other.convertToMonth();

 		assert(nb_month1>=nb_month2); // to compute the ratio only when tenor1>=tenor2
 		return (nb_month1/nb_month2);
	}

public:
	// A tenor is never to change after being instanciated
	const         char* name   ;
	const unsigned int& nbMonth;

};



/*




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
*/

#endif /* TENOR_TYPE_H */
