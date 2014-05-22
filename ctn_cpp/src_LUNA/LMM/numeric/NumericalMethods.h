#ifndef LMM_NUMERICAL_METHOD_H
#define LMM_NUMERICAL_METHOD_H

#pragma once
#include <vector>

#include <boost/math/distributions.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <ql/quantlib.hpp>
#include <ql/math/distributions/normaldistribution.hpp>


class NumericalMethods
{
public:
	
	static double d1(const double& fwd, const double& strike, const double& vol, const double& T);

	static double d2(const double& fwd, const double& strike, const double& vol, const double& T);

	// Compute a derivative's price using Black's formula
	static double Black_Price(const double& fwd, const double& strike, const double& vol, const double& T);

	static double Black_Vega(const double& fwd, const double& strike, const double& vol, const double& T);

	static double Black_Volga(const double& fwd, const double& strike, const double& vol, const double& T);

	//double impliedVolatility(const double& bs_call_price, const double& strike, const double& fwd, const double& T);

	double linearInterpolation(
							   const double& t, 
		                       const std::vector<double>& maturities,
		                       const std::vector<double>& set_of_points
							   );

	//--------- TESTS ----------//
	//void test_interpolator();
};

#endif /* LMM_NUMERICAL_METHOD_H */
