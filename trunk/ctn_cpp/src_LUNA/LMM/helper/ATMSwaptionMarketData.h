#ifndef LMM_HELPER_ATMSWAPTIONMARKETDATA_H
#define LMM_HELPER_ATMSWAPTIONMARKETDATA_H
#pragma once

#include <stdlib.h>
#include <vector>
#include <string>

#include <LMM/Name.h>

/*! \class ATMSwaptionMarketData
 *
 *  Read and handle the data of At-The-Money Swaption retreived from Bloomberg
 *
 *  - Libors                         L(0,Ti,Tj)
 *  - ZeroCoupons                    P(0,Tk)
 *  - Maturities of ZC               Tk           k=0,1...
 *
 *  - Swaption Terms                 
 *  - Swaption Maturities
 *  - Matrix of Swap Rate (Strike)
 *  - Matrix of Volatilities
 *
 *  Check the file '$LUNA_ROOT/data/input/testATMSwaption_Mkt_info.csv' to see the format
 */
class ATMSwaptionMarketData
{
public:
	
	typedef std::vector<std::vector<double> > RealMatrix;
	
	ATMSwaptionMarketData();
	
	void clear_all();
	
	void readDataFromFile(const std::string& inputfile);

	/* insert additional date in discountMaturities, and interpolate theses points 
	 * for having the appropriated inserted values in discountFactors_Mkt
	 */
	//ctntodo
	void interpolateDiscountFactors(const std::vector<double>& interpolation_dates);

	//! getters
	const std::vector<double>& get_LIBOR()             const ;
	const std::vector<double>& get_ZC_BOND()           const ;
	const std::vector<double>& get_ZC_MATURITIES()     const ;

	const std::vector<double>& get_SWPM_TERMS()        const ;
	const std::vector<double>& get_SWPM_MATURITIES()   const ;	
	
	const RealMatrix&          get_SWAPRATE_MATRIX()   const ;
	const RealMatrix&          get_VOLATILITY_MATRIX() const ;


	// ctntodo method took from MarketInfoHandler
	std::vector<double> createDiscountFactorArray() const ;
	RealMatrix chooseSwaptionMatrix(size_t horizon) const ; 
	RealMatrix chooseSwapRates     (size_t horizon) const ;
	LMM::Matrix_PairOfYears chooseSwapMaturitiesAndTenors(size_t horizon, const LMM::Matrix_PairOfYears& matrix_of_years) const ;

	void print(const std::string& filename) const;
private:

	std::vector<double> LIBOR_         ;
	std::vector<double> ZC_BOND_       ;
	std::vector<double> ZC_MATURITIES_ ;

	std::vector<double> SWPM_TERMS_      ; // list of terms of swaptions
	std::vector<double> SWPM_MATURITIES_ ; // list of maturities of swaptions
	
	RealMatrix SWAPRATE_MATRIX_     ;
	RealMatrix VOLATILITY_MATRIX_   ;	

	// functions useful for parsing data

	// The second line of Excel file containe information about Swaption Terms
	void parseTermsLine(const std::string& firstLine);

	// Convert string to appropriated double value 
	double numerical_value(std::string s) const ;

	// check if case is a Tenor, containing text as YR, MO, ...
	bool isTenor(const std::string& s)  const;

	// check if case is just label text as pillar, P, L, Expiry, ##### , empty case ...
	bool isNotUsefulCase(const std::string& s) const; 

	// functions use for converting data after read
	void convertBpToPercent();
};

#endif /* LMM_HELPER_ATMSWAPTIONMARKETDATA_H */