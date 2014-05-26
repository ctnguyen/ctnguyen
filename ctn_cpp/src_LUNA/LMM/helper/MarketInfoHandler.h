#ifndef LMM_HELPER_MARKETINFOHANDLER_H
#define LMM_HELPER_MARKETINFOHANDLER_H
#pragma once

#include <vector>

typedef std::vector<std::vector<double> > matrix_;
typedef std::vector<std::vector<std::pair<double,double> > > matrix_pairOfYears;

//-- handle data from bloomberg (interpolations,...)
class MarketInfoHandler
{
private:
	std::vector<double> libors_Mkt_;
	std::vector<double> discountFactors_Mkt_;
	std::vector<double> discountMaturities_;
	matrix_ swaptionVolMatrix_Mkt_;
	matrix_ swapRates_Mkt_;

public:
	MarketInfoHandler(const std::vector<double>& libors_Mkt,
		              const std::vector<double>& discountFactors_Mkt,
					  const std::vector<double>& discountMaturities,
					  const matrix_& swaptionVolMatrix_Mkt,
					  const matrix_& swapRates_Mkt);

	void convertBpToPercent();
	void interpolateDiscountFactors();
	std::vector<double> createDiscountFactorArray();
	matrix_ chooseSwaptionMatrix(size_t horizon); 
	matrix_ chooseSwapRates(size_t horizon);
	matrix_pairOfYears chooseSwapMaturitiesAndTenors(size_t horizon, const matrix_pairOfYears& matrix_of_years);
	
};

#endif /* LMM_HELPER_MARKETINFOHANDLER_H */
