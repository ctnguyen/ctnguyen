#include <LMM/helper/MarketInfoCollector.h>

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

using namespace std;


//-- Init static attributes
matrix_ MarketInfoCollector::swapRates_;
matrix_ MarketInfoCollector::swaptionVolatilityMatrix_;
std::vector<double> MarketInfoCollector::zeroCouponBonds_ ;
std::vector<double> MarketInfoCollector::libors_;
std::vector<double> MarketInfoCollector::zcMaturities_;


void MarketInfoCollector::readMarketInfo(const std::string& fileIn)	                    
{
	std::ifstream instream;
	instream.open(fileIn.c_str());

	matrix_ result;
	string line;
	char delimiter = '#';
	
	if (instream.is_open())
	{
		//-- Ignore the first two lines of xls file
		getline (instream,line);
		getline (instream,line);

		while (instream.good())
		{
			getline (instream,line);
			stringstream ss(line); 

			//-- If current swaption row has char '#', stop reading
			if (line.at(8) == delimiter)
				break;

			string s;
			vector<double> res;
			
			//-- Loop on each cell of the current line
			while(getline(ss,s,';'))
			{
				double convertedString = toDouble(s); // to handle float format in excel

				//-- Convert ZC maturities to year fractions
				if (s.find('D') != std::string::npos)
				{
					convertedString /= 360.;
				}
				else if (s.find('W') != std::string::npos)
				{
					convertedString /= 72.;
				}
				else if (s.find('M') != std::string::npos)
				{
					convertedString /= 12.;
				}

				res.push_back(convertedString);
			}
			result.push_back(res);
		}
	}
	else
	{
		cout << ".. hello hello ... Market Info Collector: --> Cannot open requested file" << endl;
		exit(0);
	}

	for (size_t i = 0; i < result.size(); ++i)
	{
		if (result[i][1] != 0.)
			libors_.push_back(result[i][1]);

		if (result[i][3] != 0.)
			zcMaturities_.push_back(result[i][3]);

		if (result[i][4] != 0.)
			zeroCouponBonds_.push_back(result[i][4]);
	}

	//-- Swaption matrix
	for (size_t i = 0; i < result.size(); i=i+2)
	{
		std::vector<double> swaptionmatrix_tmp;
		for (size_t j = 8; j < result[i].size(); ++j)
		{
			swaptionmatrix_tmp.push_back(result[i][j]);
		}
		swaptionVolatilityMatrix_.push_back(swaptionmatrix_tmp);
	}

	//-- Swap rates
	for (size_t i = 1; i < result.size(); i=i+2)
	{
		std::vector<double> swapRates_tmp;;
		for (size_t j = 8; j < result[i].size(); ++j)
		{
			swapRates_tmp.push_back(result[i][j]);
		}
		swapRates_.push_back(swapRates_tmp);
	}


	instream.close();
}


double MarketInfoCollector::toDouble(std::string s)
{
    std::replace(s.begin(), s.end(), ',', '.');
    return std::atof(s.c_str());
}

matrix_& MarketInfoCollector::get_swapRates(){return swapRates_;}
matrix_& MarketInfoCollector::get_swaptionVolatilityMatrix(){return swaptionVolatilityMatrix_;}
std::vector<double>& MarketInfoCollector::get_libors(){return libors_;}
std::vector<double>& MarketInfoCollector::get_zcBonds(){return zeroCouponBonds_;}
std::vector<double>& MarketInfoCollector::get_zcMaturities(){return zcMaturities_;}

