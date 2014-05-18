#define BOOST_TEST_MODULE LMM_unit_test_tenor
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <cassert>
#include <string.h>

BOOST_AUTO_TEST_SUITE(lmm_test_tenor)

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

	size_t ratioTo(const Tenor& other)
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


BOOST_AUTO_TEST_CASE(test_TenorTypePrototype_constructors)
{

	Tenor tenorNon = Tenor::_Non;
	BOOST_CHECK(tenorNon.nbMonth==0);
	BOOST_CHECK(strcmp(tenorNon.name, "_Non")==0);

	Tenor tenor1M  = Tenor::_1M;
	BOOST_CHECK( tenor1M.nbMonth == 1 );
	BOOST_CHECK(strcmp( tenor1M.name , "_1M" )==0);

	Tenor tenor3M  = Tenor::_3M;
	BOOST_CHECK( tenor3M.nbMonth == 3 );
	BOOST_CHECK(strcmp( tenor3M.name , "_3M" )==0);

	Tenor tenor6M  = Tenor::_6M;
	BOOST_CHECK( tenor6M.nbMonth == 6 );
	BOOST_CHECK(strcmp( tenor6M.name , "_6M" )==0);

	Tenor tenor9M  = Tenor::_9M;
	BOOST_CHECK( tenor9M.nbMonth == 9 );
	BOOST_CHECK(strcmp( tenor9M.name , "_9M" )==0);

	Tenor tenor12M = Tenor::_12M;
	BOOST_CHECK( tenor12M.nbMonth == 12 );
	BOOST_CHECK(strcmp( tenor12M.name , "_12M" )==0);

	Tenor tenor1Y  = Tenor::_1Y;
	BOOST_CHECK( tenor1Y.nbMonth == 12 );
	BOOST_CHECK(strcmp( tenor1Y.name , "_1Y" )==0);
}

BOOST_AUTO_TEST_CASE(test_TenorTypePrototype_comparing)
{
	Tenor tenorNon1 = Tenor::_Non;
	Tenor tenorNon2 = Tenor::_Non;
	BOOST_CHECK(tenorNon1 == tenorNon2);

	Tenor tenor12M = Tenor::_12M;
	Tenor tenor1Y  = Tenor::_1Y;
	BOOST_CHECK(tenor12M == tenor1Y);

	BOOST_CHECK(tenorNon1 != tenor12M);

	BOOST_CHECK( !tenorNon1.isValidTenor() );
	BOOST_CHECK( tenor12M.isValidTenor() );
}

BOOST_AUTO_TEST_CASE(test_TenorTypePrototype_calculus)
{
	Tenor tenor1M  = Tenor::_1M;
	Tenor tenor3M  = Tenor::_3M;
	Tenor tenor6M  = Tenor::_6M;
	Tenor tenor9M  = Tenor::_9M;
	Tenor tenor12M = Tenor::_12M;
	Tenor tenor1Y  = Tenor::_1Y;

	BOOST_CHECK(tenor1Y.convertToMonth()  == 12 );
	BOOST_CHECK(tenor12M.convertToMonth() == 12 );
	BOOST_CHECK(tenor6M.convertToMonth()  == 6  );

	BOOST_CHECK(tenor3M.convertToYear()  == 0.25 );
	BOOST_CHECK(tenor6M.convertToYear()   == 0.5 );
	BOOST_CHECK(tenor12M.convertToYear()  == 1.0 );

	BOOST_CHECK(tenor12M.ratioTo(tenor1Y)  == 1 );
	BOOST_CHECK(tenor12M.ratioTo(tenor9M)  == 1 );
	BOOST_CHECK(tenor12M.ratioTo(tenor3M)  == 4 );
	BOOST_CHECK(tenor12M.ratioTo(tenor6M)  == 2 );
}

BOOST_AUTO_TEST_SUITE_END()
