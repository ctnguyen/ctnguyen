#pragma once
#include <vector>

#ifndef LMM_NUMERICAL_METHOD_H
#define LMM_NUMERICAL_METHOD_H

class NumericalMethods
{
public:
	
	static double d1(double fwd,
		double strike,
		double vol,
		double T);

	static double d2(double fwd,
		double strike,
		double vol,
		double T);

	// Compute a derivative's price using Black's formula
	static double Black_Price(double fwd,
		double strike,
		double vol,
		double T);

	static double Black_Vega(double fwd,
		double strike,
		double vol,
		double T); 

	static double Black_Volga(double fwd,
		double strike,
		double vol,
		double T);

	//double impliedVolatility(double bs_call_price, 							  
	//						 double strike, 
	//						 double fwd,
	//						 double T);

	double linearInterpolation(double t, 
		                       const std::vector<double>& maturities,
		                       const std::vector<double>& set_of_points);

	//--------- TESTS ----------//
	//void test_interpolator();
};

#endif /* LMM_NUMERICAL_METHOD_H */