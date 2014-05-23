#define BOOST_TEST_MODULE LMM_unit_test_helper_MarketInfoCollector
#include <boost/test/included/unit_test.hpp>

/*
#include <fstream>
#include <iostream>
#include <sstream>

*/

#include <string>

#include <LMM/generic_path.h>

#include <LMM/helper/MarketInfoCollector.h>

BOOST_AUTO_TEST_SUITE(lmm_test_helper_marketinfocollector)

BOOST_AUTO_TEST_CASE(test_marketinfocollector)
{
	
	std::string path_FileIn = LMM::get_runtime_datapath() + "Mkt_info_1.csv";
	std::cout<< "File Input Paht :"<< path_FileIn << std::endl;


	//std::ifstream inputFile;
	//inputFile.open(path_FileIn);
	MarketInfoCollector::readMarketInfo( path_FileIn );
	//inputFile.close();

	std::vector<double> libors_BB = MarketInfoCollector::get_libors();
	std::vector<double> zc_BB = MarketInfoCollector::get_zcBonds();
	matrix_ swaptionMatrix_BB = MarketInfoCollector::get_swaptionVolatilityMatrix();
	matrix_ swaprates_BB = MarketInfoCollector::get_swapRates();


	//-- Put all results in Excel
	std::string path_FileOut = LMM::get_output_path() + "test_MarketInfoCollector.csv";
	std::cout<< "File Output Path :"<< path_FileOut << std::endl;
	std::ofstream outputFile;
	outputFile.open(path_FileOut);

	outputFile << "LIBORS" << std::endl;
	for each (double lib_bb in libors_BB)
		outputFile << lib_bb << ";";

	outputFile << std::endl << std::endl;

	outputFile << "ZC BONDS" << std::endl;
	for each (double zc_bb in zc_BB)
		outputFile << zc_bb << ";";

	outputFile << std::endl << std::endl;

	outputFile << "ATM SWAPTION VOL MATRIX" << std::endl;
	for each (std::vector<double> swpMatRow in swaptionMatrix_BB)
	{
		for each (double swpVol in swpMatRow)
			outputFile << swpVol << ";";

		outputFile << std::endl;
	}
	outputFile << std::endl;


	outputFile << "SWAP RATES" << std::endl;
	for each (std::vector<double> swpRateRow in swaprates_BB)
	{
		for each (double swpR in swpRateRow)
			outputFile << swpR << ";";

		outputFile << std::endl;
	}
	outputFile << std::endl;

	outputFile.close();

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()