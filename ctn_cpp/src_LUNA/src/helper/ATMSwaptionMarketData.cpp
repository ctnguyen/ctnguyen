#include <LMM/helper/ATMSwaptionMarketData.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

#include <LMM/generic_path.h>
#include <LMM/numeric/Interpolation.h>


ATMSwaptionMarketData::ATMSwaptionMarketData()
{

}

const std::vector<double>&               ATMSwaptionMarketData::get_LIBOR()             const { return LIBOR_             ; }
const std::vector<double>&               ATMSwaptionMarketData::get_ZC_BOND()           const { return ZC_BOND_           ; }
const std::vector<double>&               ATMSwaptionMarketData::get_ZC_MATURITIES()     const { return ZC_MATURITIES_     ; }
const std::vector<double>&               ATMSwaptionMarketData::get_SWPM_TERMS()        const { return SWPM_TERMS_        ; } 
const std::vector<double>&               ATMSwaptionMarketData::get_SWPM_MATURITIES()   const { return SWPM_MATURITIES_   ; }	
const ATMSwaptionMarketData::RealMatrix& ATMSwaptionMarketData::get_SWAPRATE_MATRIX()   const { return SWAPRATE_MATRIX_   ; }
const ATMSwaptionMarketData::RealMatrix& ATMSwaptionMarketData::get_VOLATILITY_MATRIX() const { return VOLATILITY_MATRIX_ ; }
	


void ATMSwaptionMarketData::readDataFromFile(const std::string& fileIn)
{
	std::ifstream instream;
	instream.open(fileIn.c_str());

	RealMatrix result;
	std::string line;
	char delimiter = '#';

	if (instream.is_open())
	{
		//-- Ignore the first two lines of xls file
		getline (instream,line);
		getline (instream,line);

		this->parseTermsLine(line);

		while (instream.good())
		{
			getline (instream,line);
			std::stringstream ss(line); 

			//-- first column and 3th column are empty and the 6th column is ########, then that say terminated
			if (line.at(0) == ';' && line.at(3) == ';' && line.at(6) ==  delimiter) break;

			std::string s;
			std::vector<double> res;

			//-- Loop on each cell of the current line
			while(getline(ss,s,';'))
			{
				double convertedString = this->numerical_value(s); // to handle float format in excel

				res.push_back(convertedString);
			}

			// pop back zeros at the en of reading line
			while (!res.empty() && res.back() == 0.0 ) res.pop_back();

			result.push_back(res);
		}
	}
	else
	{
		std::cout << "LMM ATMSwaptionMarketData::readDataFromFile --> Cannot open requested file" << std::endl << fileIn<< std::endl ;
		exit(0);
	}

	for (size_t i = 0; i < result.size(); ++i)
	{
		if (result[i][1] != 0.) LIBOR_.push_back(result[i][1]);           // second column

		if (result[i][3] != 0.)	ZC_MATURITIES_.push_back(result[i][3]);   // 4th column

		if (result[i][4] != 0.)	ZC_BOND_.push_back(result[i][4]);         // 5th column		
	}

	//-- Swaption matrix
	for (size_t i = 0; i < result.size(); i=i+2)
	{
		std::vector<double> swaptionRealMatrixtmp;
		for (size_t j = 8; j < result[i].size(); ++j)
		{
			swaptionRealMatrixtmp.push_back(result[i][j]);
		}

		VOLATILITY_MATRIX_.push_back(swaptionRealMatrixtmp);

		SWPM_MATURITIES_.push_back(result[i][6]);             // 7th column
	}

	//-- Swap rates
	for (size_t i = 1; i < result.size(); i=i+2)
	{
		std::vector<double> swapRates_tmp;;
		for (size_t j = 8; j < result[i].size(); ++j)
		{
			swapRates_tmp.push_back(result[i][j]);
		}
		SWAPRATE_MATRIX_.push_back(swapRates_tmp);
	}

	this->convertBpToPercent();

	instream.close();
}


void ATMSwaptionMarketData::clear_all()
{

	LIBOR_.clear();
	ZC_BOND_.clear();
	ZC_MATURITIES_.clear();

	SWPM_TERMS_.clear();
	SWPM_MATURITIES_.clear();
		
	for (auto swpMatRow : VOLATILITY_MATRIX_){ swpMatRow.clear(); }
	VOLATILITY_MATRIX_.clear();

	for (auto swpRateRow : SWAPRATE_MATRIX_){	swpRateRow.clear();	}
	SWAPRATE_MATRIX_.clear();
}


void ATMSwaptionMarketData::parseTermsLine(const std::string& firstLine)
{
	std::stringstream ss(firstLine) ; std::string s ;
	
	//-- Loop on each cell of the current line
	while(getline(ss,s,';'))
	{
		double term = numerical_value(s); // to handle float format in excel

		if(term != 0.)	SWPM_TERMS_.push_back(term);
	}
}





double ATMSwaptionMarketData::numerical_value(std::string s) const
{
	if ( isNotUsefulCase(s) ) return 0;

	if ( isTenor(s) )
	{
		// calculate for tenors in Year unit "YR", "Y"
		size_t foundYR = s.find("YR");
		if(foundYR != std::string::npos ) 
		{
			s.erase(foundYR, 2);          // if found "YR", remove two characters
			return std::atof(s.c_str());  // the string left is tenor in year unit
		}
		size_t foundY = s.find("Y");
		if(foundY != std::string::npos ) 
		{
			s.erase(foundY, 1);           // if found "Y", remove 1 character
			return std::atof(s.c_str());  // the string left is tenor in year unit
		}

		// calculate for tenors in Month unit "MO", "M"
		size_t foundMO = s.find("MO");
		if(foundMO != std::string::npos ) 
		{
			s.erase(foundMO, 2);             // if found "MO", remove two characters
			return std::atof(s.c_str())/12.; // the string left is tenor in month unit
		}
		size_t foundM = s.find("M");
		if(foundM != std::string::npos ) 
		{
			s.erase(foundM, 1);              // if found "M", remove 1 characters
			return std::atof(s.c_str())/12.; // the string left is tenor in month unit
		}


		// calculate for tenors in Week unit
		size_t foundW = s.find("W");
		if(foundW != std::string::npos ) 
		{
			s.erase(foundW, 1);              // if found "W", remove 1 characters
			return std::atof(s.c_str())/72.; // the string left is tenor in week unit
		}

		// calculate for tenors in Day unit
		size_t foundD = s.find("D");
		if(foundD != std::string::npos ) 
		{
			s.erase(foundD, 1);               // if found "D", remove 1 characters
			return std::atof(s.c_str())/360.; // the string left is tenor in day unit
		}
	}

	std::replace(s.begin(), s.end(), ',', '.');
	return std::atof(s.c_str());
}

bool ATMSwaptionMarketData::isTenor(const std::string& s) const
{
	// if text contain 'Y' or 'M' , that is a tenor 
	return (s.find('Y') != std::string::npos || s.find('M') != std::string::npos || s.find('W') != std::string::npos || s.find('D') != std::string::npos ) ;
}

bool ATMSwaptionMarketData::isNotUsefulCase(const std::string& s) const
{
	return (s.empty()||s[0] ==' '|| s[0] == 'p' || s[0] == 'L' || s[0] == 'P' || s[0] == 'E' || s[0] == '#');
}


void ATMSwaptionMarketData::convertBpToPercent()
{
	for (auto lib_bb : LIBOR_)
			lib_bb *= 0.01;

	for (auto swaptionVolRow : VOLATILITY_MATRIX_)
	{
		for (auto swaptionVol : swaptionVolRow)
			swaptionVol *= 0.01;
	}

	for (auto swapRateRow : SWAPRATE_MATRIX_)
	{
		for (auto swaprate : swapRateRow)
			swaprate *= 0.01;
	}
}

void ATMSwaptionMarketData::interpolateDiscountFactors(const std::vector<double>& interpolation_dates)
{
	numeric::Interpolation interpolator;

	for (auto inter_date : interpolation_dates)
		interpolator.linearInterpolation(ZC_BOND_,ZC_MATURITIES_,inter_date);
}

std::vector<double> ATMSwaptionMarketData::createDiscountFactorArray() const
{
	 //-- the zc bond vector to use
	std::vector<double> zcVector_BB = ZC_BOND_;//ctntodo for instant use the same as discountFactors imported from data

	/* BAD
	//-- Choose mkt discount factors with maturities = 6M, 1Y, 18M, 2Y,...
	zcVector_BB.push_back(1.);
	zcVector_BB.push_back(ZC_BOND_[9]);
	zcVector_BB.push_back(ZC_BOND_[15]);
	zcVector_BB.push_back(ZC_BOND_[17]);
	zcVector_BB.push_back(ZC_BOND_[19]);
	zcVector_BB.push_back(ZC_BOND_[21]);
	zcVector_BB.push_back(ZC_BOND_[23]);
	zcVector_BB.push_back(ZC_BOND_[25]);
	zcVector_BB.push_back(ZC_BOND_[27]);

	//-- Add interpolated discount factors 
	for (size_t i = 28; i < ZC_BOND_.size(); ++i)
		zcVector_BB.push_back(ZC_BOND_[i]);
		*/
	return zcVector_BB;
}

ATMSwaptionMarketData::RealMatrix ATMSwaptionMarketData::chooseSwaptionMatrix(size_t horizon) const
{
	RealMatrix selectedSwaptionMatrix;

	// Start at maturity = 1Y
	size_t cpt = 0;
	for (size_t i = 4; i < horizon+4; ++i)// ctntodo why choose 4 here
	{
		std::vector<double> swaptionMatRow;
		for (size_t j = 0; j < horizon-cpt; ++j)
		{
			const double & vol = VOLATILITY_MATRIX_[i][j];
			swaptionMatRow.push_back(vol);
		}
		selectedSwaptionMatrix.push_back(swaptionMatRow);
		cpt++;
	}
	return selectedSwaptionMatrix;
}

ATMSwaptionMarketData::RealMatrix ATMSwaptionMarketData::chooseSwapRates(size_t horizon) const
{
	RealMatrix selectedSwapRateMatrix;

	// Start at maturity = 1Y
	size_t cpt = 0;
	for (size_t i = 4; i < horizon+4; ++i)// ctntodo why choose 4 here
	{
		std::vector<double> swaprateMatRow;
		for (size_t j = 0; j < horizon-cpt; ++j)
		{
			const double & vol = SWAPRATE_MATRIX_[i][j];
			swaprateMatRow.push_back(vol);
		}
		selectedSwapRateMatrix.push_back(swaprateMatRow);
		cpt++;
	}
	return selectedSwapRateMatrix;
}

LMM::Matrix_PairOfYears ATMSwaptionMarketData::chooseSwapMaturitiesAndTenors(size_t horizon, const LMM::Matrix_PairOfYears& matrix_of_years) const
{
	LMM::Matrix_PairOfYears res;

	//-- Select pairs of years until wanted horizon is reached
	for (size_t i = 1; i <= horizon; ++i) //-- ignore first row
	{
		std::vector<std::pair<double,double> > row;
		for (size_t j = 1; j <= horizon-i+1; ++j) //-- ignore first column
		{
			row.push_back(matrix_of_years[i][j]);
		}
		res.push_back(row);
	}
	return res;
}


























void ATMSwaptionMarketData::print(const std::string& filename) const
{
	std::string path_FileOut = LMM::get_output_path() + filename;

	std::ofstream outputFile  ;  outputFile.open(path_FileOut.c_str() );

	outputFile << "- LIBORS ---" << std::endl;
	for (auto lib_bb : LIBOR_) outputFile <<" "<< lib_bb << ";";
	outputFile << std::endl << std::endl;

	outputFile << "- ZC BONDS ---" << std::endl;
	for (auto zc_bb : ZC_BOND_) outputFile <<" "<<zc_bb << ";";
	outputFile << std::endl << std::endl;

	outputFile << "- ZC MATURITIES ---" << std::endl;
	for (auto zc_m : ZC_MATURITIES_) outputFile <<" "<<zc_m << ";";
	outputFile << std::endl << std::endl<< std::endl;



	outputFile << "- SWPN TERMS ---" << std::endl;
	for (auto swpn_t : SWPM_TERMS_) outputFile <<" "<<swpn_t << ";";
	outputFile << std::endl << std::endl;

	outputFile << "- SWPN MATURITIES ---" << std::endl;
	for (auto swpn_m : SWPM_MATURITIES_) outputFile <<" "<<swpn_m << ";";
	outputFile << std::endl << std::endl;

	outputFile <<  "=======    ATM SWAPTION VOL MATRIX   ========" << std::endl;
	for (auto swpMatRow : VOLATILITY_MATRIX_)
	{
		for (auto swpVol : swpMatRow) outputFile <<" "<< swpVol << ";";
		outputFile << std::endl;
	}
	outputFile << std::endl << std::endl;

	outputFile << "=======    SWAP RATES   =========" << std::endl;
	for (auto swpRateRow : SWAPRATE_MATRIX_)
	{
		for (auto swpR : swpRateRow) outputFile <<" "<< swpR << ";";
		outputFile << std::endl;
	}
	outputFile << std::endl;

	outputFile.close();	
}