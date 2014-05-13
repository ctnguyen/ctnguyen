//#include "MarketInfoHandler.h"
//#include "Interpolation.h"
//
//MarketInfoHandler::MarketInfoHandler(const std::vector<double>& libors_Mkt,
//									 const std::vector<double>& discountFactors_Mkt,
//									 const std::vector<double>& discountMaturities,
//									 const matrix_& swaptionVolMatrix_Mkt,
//									 const matrix_& swapRates_Mkt)
//
//									 : libors_Mkt_(libors_Mkt), discountFactors_Mkt_(discountFactors_Mkt), 
//									   discountMaturities_(discountMaturities),swaptionVolMatrix_Mkt_(swaptionVolMatrix_Mkt), 
//									   swapRates_Mkt_(swapRates_Mkt)
//{}
//
//void MarketInfoHandler::convertBpToPercent()
//{
//	for each (double lib_bb in libors_Mkt_)
//			lib_bb *= 0.01;
//
//	for each (std::vector<double> swaptionVolRow in swaptionVolMatrix_Mkt_)
//	{
//		for each (double swaptionVol in swaptionVolRow)
//			swaptionVol *= 0.01;
//	}
//
//	for each (std::vector<double> swapRateRow in swapRates_Mkt_)
//	{
//		for each (double swaprate in swapRateRow)
//			swaprate *= 0.01;
//	}
//}
//
//void MarketInfoHandler::interpolateDiscountFactors()
//{
//	std::vector<double> interpolation_dates;
//	interpolation_dates.push_back(4.5);
//	interpolation_dates.push_back(5.5);
//	interpolation_dates.push_back(6.5);
//	interpolation_dates.push_back(7.5);
//	interpolation_dates.push_back(8.5);
//	interpolation_dates.push_back(9.5);
//	interpolation_dates.push_back(10.5);
//
//	NumericalTools::Interpolation interpolator;
//	std::vector<double> interpolated_zc_values;
//	std::vector<double> tenorDates_cpy = discountMaturities_; //-- Will be modified after every interpolation
//
//	for each (double inter_date in interpolation_dates)
//		interpolator.linearInterpolation(discountFactors_Mkt_,tenorDates_cpy,inter_date);
//}
//
//std::vector<double> MarketInfoHandler::createDiscountFactorArray()
//{
//	std::vector<double> zcVector_BB; //-- the zc bond vector to use
//
//	//-- Choose mkt discount factors with maturities = 6M, 1Y, 18M, 2Y,...
//	zcVector_BB.push_back(1.);
//	zcVector_BB.push_back(discountFactors_Mkt_[9]);
//	zcVector_BB.push_back(discountFactors_Mkt_[15]);
//	zcVector_BB.push_back(discountFactors_Mkt_[17]);
//	zcVector_BB.push_back(discountFactors_Mkt_[19]);
//	zcVector_BB.push_back(discountFactors_Mkt_[21]);
//	zcVector_BB.push_back(discountFactors_Mkt_[23]);
//	zcVector_BB.push_back(discountFactors_Mkt_[25]);
//	zcVector_BB.push_back(discountFactors_Mkt_[27]);
//
//	//-- Add interpolated discount factors 
//	for (size_t i = 28; i < discountFactors_Mkt_.size(); ++i)
//		zcVector_BB.push_back(discountFactors_Mkt_[i]);
//
//	return zcVector_BB;
//}
//
//matrix_ MarketInfoHandler::chooseSwaptionMatrix(size_t horizon)
//{
//	matrix_ selectedSwaptionMatrix;
//
//	// Start at maturity = 1Y
//	size_t cpt = 0;
//	for (size_t i = 4; i < horizon+4; ++i)
//	{
//		std::vector<double> swaptionMatRow;
//		for (size_t j = 0; j < horizon-cpt; ++j)
//		{
//			double vol = swaptionVolMatrix_Mkt_[i][j];
//			swaptionMatRow.push_back(vol);
//		}
//		selectedSwaptionMatrix.push_back(swaptionMatRow);
//		cpt++;
//	}
//	return selectedSwaptionMatrix;
//}
//
//matrix_ MarketInfoHandler::chooseSwapRates(size_t horizon)
//{
//	matrix_ selectedSwapRateMatrix;
//
//	// Start at maturity = 1Y
//	size_t cpt = 0;
//	for (size_t i = 4; i < horizon+4; ++i)
//	{
//		std::vector<double> swaprateMatRow;
//		for (size_t j = 0; j < horizon-cpt; ++j)
//		{
//			double vol = swapRates_Mkt_[i][j];
//			swaprateMatRow.push_back(vol);
//		}
//		selectedSwapRateMatrix.push_back(swaprateMatRow);
//		cpt++;
//	}
//	return selectedSwapRateMatrix;
//}
//
//matrix_pairOfYears MarketInfoHandler::chooseSwapMaturitiesAndTenors(size_t horizon, const matrix_pairOfYears& matrix_of_years)
//{
//	matrix_pairOfYears res;
//
//	//-- Select pairs of years until wanted horizon is reached
//	for (size_t i = 1; i <= horizon; ++i) //-- ignore first row
//	{
//		std::vector<std::pair<double,double>> row;
//		for (size_t j = 1; j <= horizon-i+1; ++j) //-- ignore first column
//		{
//			row.push_back(matrix_of_years[i][j]);
//		}
//		res.push_back(row);
//	}
//	return res;
//}