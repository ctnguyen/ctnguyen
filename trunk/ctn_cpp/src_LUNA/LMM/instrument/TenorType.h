#ifndef LMM_INSTRUMENT_TENOR_TYPE_H
#define LMM_INSTRUMENT_TENOR_TYPE_H
#pragma once


#include <map>
#include <string>
#include <cassert>

/*! \class Tenor
 *  This class model the Tenor Type 1M,2M ... 12M
 *  Its design is an advanced of and enumeration, who can have instance and method
 * User can do
 * Tenor m_tenor=Tenor::3M;
 * and use all method of Tenor 
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
		TenorType(){};
		static const char*        NAME     ;
		static const unsigned int NB_MONTH ;
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

std::ostream& operator<<(std::ostream& os, const Tenor& tenor);

#endif /* LMM_INSTRUMENT_TENOR_TYPE_H */
