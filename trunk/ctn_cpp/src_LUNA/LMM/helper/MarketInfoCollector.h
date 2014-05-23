#ifndef LMM_HELPER_MARKETINFOCOLLECTOR_H
#define LMM_HELPER_MARKETINFOCOLLECTOR_H
#pragma once


#include <cstring>
#include <fstream>
#include <vector>

typedef std::vector<std::vector<double> > matrix_;

class MarketInfoCollector
{
private:
	static matrix_ swapRates_;
	static matrix_ swaptionVolatilityMatrix_;
	static std::vector<double> libors_;
	static std::vector<double> zeroCouponBonds_;
	static std::vector<double> zcMaturities_;

public:

	static void readMarketInfo(std::ifstream& fin);
		                
	//-- Getters --//
	static matrix_& get_swapRates();
	static matrix_& get_swaptionVolatilityMatrix();
	static std::vector<double>& get_libors();
	static std::vector<double>& get_zcBonds();
	static std::vector<double>& get_zcMaturities();

	// Convert string to double written with '.'
	static double toDouble(std::string s);

	static void test_reader();
};


#endif /* LMM_HELPER_MARKETINFOCOLLECTOR_H */