#define BOOST_TEST_MODULE LMM_unit_test_TenorPrototype
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <cassert>
#include <string.h>

BOOST_AUTO_TEST_SUITE(lmm_test_TenorPrototype)

/*! To factorize, the class 'TenorPrototype' will replace the 'TenorPrototypeTypeEnum::TenorPrototypeTypeEnum'
 *
 */
class TenorPrototype
{
public:

	/*! To define a new TenorPrototypeType, user has to define
	 * - TYPEID   of TenorPrototype type
	 * - NAME     of TenorPrototype type
	 * - NB_MONTH number of month of TenorPrototype type
	 * by specializing this template
	 */
	template<unsigned int TYPEID> class TenorPrototypeType
	{
	public :
		static const char*        NAME     ;
		static const unsigned int NB_MONTH ;

		TenorPrototypeType(){}
	};

	static const TenorPrototypeType<0>  _Non;typedef TenorPrototypeType<0> TYPE_0;
	static const TenorPrototypeType<1>   _1M;typedef TenorPrototypeType<1> TYPE_1;
	static const TenorPrototypeType<2>   _3M;typedef TenorPrototypeType<2> TYPE_2;
	static const TenorPrototypeType<3>   _6M;typedef TenorPrototypeType<3> TYPE_3;
	static const TenorPrototypeType<4>   _9M;typedef TenorPrototypeType<4> TYPE_4;
	static const TenorPrototypeType<5>  _12M;typedef TenorPrototypeType<5> TYPE_5;
	static const TenorPrototypeType<6>   _1Y;typedef TenorPrototypeType<6> TYPE_6;


	//! Constructor build a TenorPrototype by giving its type
	template<unsigned int NBMONTH>
	TenorPrototype(const TenorPrototypeType<NBMONTH>&):name(TenorPrototypeType<NBMONTH>::NAME),nbMonth(TenorPrototypeType<NBMONTH>::NB_MONTH){}

	//! check if two TenorPrototype is equal
	bool operator==(const TenorPrototype& other) const { return (nbMonth == other.nbMonth); }
	bool operator!=(const TenorPrototype& other) const { return (nbMonth != other.nbMonth); }

	bool isValidTenorPrototype()     const { return nbMonth>0;    }

	double convertToYear()  const { assert( this->isValidTenorPrototype() ); return nbMonth/12.0;}
	size_t convertToMonth() const { assert( this->isValidTenorPrototype() ); return nbMonth;}

	size_t ratioTo(const TenorPrototype& other)
	{
		assert( this->isValidTenorPrototype() );assert( other.isValidTenorPrototype() );

		size_t nb_month1 = this->convertToMonth();
 		size_t nb_month2 = other.convertToMonth();

 		assert(nb_month1>=nb_month2); // to compute the ratio only when TenorPrototype1>=TenorPrototype2
 		return (nb_month1/nb_month2);
	}

public:
	// A TenorPrototype is never to change after being instanciated
	const         char* name   ;
	const unsigned int& nbMonth;

};

template<> const char* TenorPrototype::TYPE_0::NAME = "_Non";template<> const unsigned int TenorPrototype::TYPE_0::NB_MONTH =  0;
template<> const char* TenorPrototype::TYPE_1::NAME =  "_1M";template<> const unsigned int TenorPrototype::TYPE_1::NB_MONTH =  1;
template<> const char* TenorPrototype::TYPE_2::NAME =  "_3M";template<> const unsigned int TenorPrototype::TYPE_2::NB_MONTH =  3;
template<> const char* TenorPrototype::TYPE_3::NAME =  "_6M";template<> const unsigned int TenorPrototype::TYPE_3::NB_MONTH =  6;
template<> const char* TenorPrototype::TYPE_4::NAME =  "_9M";template<> const unsigned int TenorPrototype::TYPE_4::NB_MONTH =  9;
template<> const char* TenorPrototype::TYPE_5::NAME = "_12M";template<> const unsigned int TenorPrototype::TYPE_5::NB_MONTH = 12;
template<> const char* TenorPrototype::TYPE_6::NAME =  "_1Y";template<> const unsigned int TenorPrototype::TYPE_6::NB_MONTH = 12;

const TenorPrototype::TYPE_0 TenorPrototype::_Non;// initialization static variable
const TenorPrototype::TYPE_1 TenorPrototype::_1M;// initialization static variable
const TenorPrototype::TYPE_2 TenorPrototype::_3M;// initialization static variable
const TenorPrototype::TYPE_3 TenorPrototype::_6M;// initialization static variable
const TenorPrototype::TYPE_4 TenorPrototype::_9M;// initialization static variable
const TenorPrototype::TYPE_5 TenorPrototype::_12M;// initialization static variable
const TenorPrototype::TYPE_6 TenorPrototype::_1Y;// initialization static variable


BOOST_AUTO_TEST_CASE(test_TenorPrototypeTypePrototype_constructors)
{

	TenorPrototype TenorPrototypeNon = TenorPrototype::_Non;
	BOOST_CHECK(TenorPrototypeNon.nbMonth==0);
	BOOST_CHECK(strcmp(TenorPrototypeNon.name, "_Non")==0);

	TenorPrototype TenorPrototype1M  = TenorPrototype::_1M;
	BOOST_CHECK( TenorPrototype1M.nbMonth == 1 );
	BOOST_CHECK(strcmp( TenorPrototype1M.name , "_1M" )==0);

	TenorPrototype TenorPrototype3M  = TenorPrototype::_3M;
	BOOST_CHECK( TenorPrototype3M.nbMonth == 3 );
	BOOST_CHECK(strcmp( TenorPrototype3M.name , "_3M" )==0);

	TenorPrototype TenorPrototype6M  = TenorPrototype::_6M;
	BOOST_CHECK( TenorPrototype6M.nbMonth == 6 );
	BOOST_CHECK(strcmp( TenorPrototype6M.name , "_6M" )==0);

	TenorPrototype TenorPrototype9M  = TenorPrototype::_9M;
	BOOST_CHECK( TenorPrototype9M.nbMonth == 9 );
	BOOST_CHECK(strcmp( TenorPrototype9M.name , "_9M" )==0);

	TenorPrototype TenorPrototype12M = TenorPrototype::_12M;
	BOOST_CHECK( TenorPrototype12M.nbMonth == 12 );
	BOOST_CHECK(strcmp( TenorPrototype12M.name , "_12M" )==0);

	TenorPrototype TenorPrototype1Y  = TenorPrototype::_1Y;
	BOOST_CHECK( TenorPrototype1Y.nbMonth == 12 );
	BOOST_CHECK(strcmp( TenorPrototype1Y.name , "_1Y" )==0);
}

BOOST_AUTO_TEST_CASE(test_TenorPrototypeTypePrototype_comparing)
{
	TenorPrototype TenorPrototypeNon1 = TenorPrototype::_Non;
	TenorPrototype TenorPrototypeNon2 = TenorPrototype::_Non;
	BOOST_CHECK(TenorPrototypeNon1 == TenorPrototypeNon2);

	TenorPrototype TenorPrototype12M = TenorPrototype::_12M;
	TenorPrototype TenorPrototype1Y  = TenorPrototype::_1Y;
	BOOST_CHECK(TenorPrototype12M == TenorPrototype1Y);

	BOOST_CHECK(TenorPrototypeNon1 != TenorPrototype12M);

	BOOST_CHECK( !TenorPrototypeNon1.isValidTenorPrototype() );
	BOOST_CHECK( TenorPrototype12M.isValidTenorPrototype() );
}

BOOST_AUTO_TEST_CASE(test_TenorPrototypeTypePrototype_calculus)
{
	TenorPrototype TenorPrototype1M  = TenorPrototype::_1M;
	TenorPrototype TenorPrototype3M  = TenorPrototype::_3M;
	TenorPrototype TenorPrototype6M  = TenorPrototype::_6M;
	TenorPrototype TenorPrototype9M  = TenorPrototype::_9M;
	TenorPrototype TenorPrototype12M = TenorPrototype::_12M;
	TenorPrototype TenorPrototype1Y  = TenorPrototype::_1Y;

	BOOST_CHECK(TenorPrototype1Y.convertToMonth()  == 12 );
	BOOST_CHECK(TenorPrototype12M.convertToMonth() == 12 );
	BOOST_CHECK(TenorPrototype6M.convertToMonth()  == 6  );

	BOOST_CHECK(TenorPrototype3M.convertToYear()  == 0.25 );
	BOOST_CHECK(TenorPrototype6M.convertToYear()   == 0.5 );
	BOOST_CHECK(TenorPrototype12M.convertToYear()  == 1.0 );

	BOOST_CHECK(TenorPrototype12M.ratioTo(TenorPrototype1Y)  == 1 );
	BOOST_CHECK(TenorPrototype12M.ratioTo(TenorPrototype9M)  == 1 );
	BOOST_CHECK(TenorPrototype12M.ratioTo(TenorPrototype3M)  == 4 );
	BOOST_CHECK(TenorPrototype12M.ratioTo(TenorPrototype6M)  == 2 );
}

BOOST_AUTO_TEST_SUITE_END()
