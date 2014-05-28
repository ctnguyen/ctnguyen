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

std::ostream& operator<<(std::ostream& os, const Tenor& tenor)
{
	os<<"Tenor" << tenor.name;	return os; 
}
