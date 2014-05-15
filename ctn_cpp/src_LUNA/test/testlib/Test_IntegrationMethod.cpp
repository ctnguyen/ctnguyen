#include <ql/math/integrals/simpsonintegral.hpp>
#include <boost/function.hpp>
#include <cmath>
#include <iostream>

#include <test/testlib/Test.h>


double lnFunc(double x){return std::log(x);}
double xCubicFunc(double x){return x*x*x;}

//! \int_{0}^{1} ln(x) dx
void test_Simpsonintegral()
{
    boost::function<double (double)> func;
	//func = lnFunc;
	func = xCubicFunc;

	double absoluteAccuracy = 1e-4;
	size_t maxEvaluations   = 1e3;

	QuantLib::SimpsonIntegral numInt(absoluteAccuracy, maxEvaluations);

	double boundLower = 0;
	double boundUpper = 1;


	std::cout << "int_{0}^{1} ln(x) dx = " << numInt(func, boundLower, boundUpper) << std::endl;
}

void test_InegrationMethod()
{
	test_Simpsonintegral();
}