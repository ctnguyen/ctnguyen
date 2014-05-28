#define BOOST_TEST_MODULE LMM_unit_test_instrument_VanillaSwap

#include <string>
#include <fstream>

#include <boost/test/included/unit_test.hpp>

#include <LMM/Name.h>
#include <LMM/generic_path.h>
#include <LMM/instrument/TenorType.h>

#include <LMM/instrument/VanillaSwap.h>


BOOST_AUTO_TEST_SUITE(lmm_instrument_VanillaSwap)

BOOST_AUTO_TEST_CASE(test_VanillaSwap_constructor)
{
	const double strike = 10.;
	LMM::Index startIndex = 2;
	LMM::Index endIndex   = 11;

	Tenor FixedTenor = Tenor::_9M;
	Tenor FloatTenor = Tenor::_3M;
	Tenor LMMTenor   = Tenor::_3M;

	LMM::VanillaSwap swap(strike, startIndex, endIndex, FloatTenor, FixedTenor, LMMTenor);

	std::string path_OutPut = LMM::get_output_path() + "unitTest_instrument_VanillaSwap.txt";
	std::ofstream swapoutput;
	swapoutput.open(path_OutPut.c_str());
	swapoutput<<swap<<std::endl;
	swapoutput.close();

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
