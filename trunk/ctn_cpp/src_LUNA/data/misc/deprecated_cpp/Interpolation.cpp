//#include <iostream>
//#include <algorithm>
//#include "Interpolation.h"
//
//
//using namespace NumericalTools;
//
//
//void Interpolation::linearInterpolation(std::vector<double>& y,
//	                                    std::vector<double>& x,
//	                                    double x_interp)
//{
//	
//	if (x_interp < x[0] || x_interp > x[x.size()-1])
//	{
//		throw("Interpolation.cpp ----> Error: invalid absciss input");
//	}
//	//-- Search the libor maturities bounding maturity_date
//	size_t index_interp = 0;
//	for (size_t i = 0; i < x.size(); ++i) 
//	{
//		if (x_interp > x[i])
//			index_interp++;
//	}
//
//	//-- Set the dates before and after maturity_date
//	double date_prev = x[index_interp-1];
//	double date_next = x[index_interp];
//
//	//-- Search in the libor matrix for libors corresponding to the previous dates
//	double libor_prev =  y[index_interp-1];
//	double libor_next = y[index_interp];
//
//	double coeff_1 = (date_next - x_interp)/(date_next - date_prev);
//	double coeff_2 = (x_interp - date_prev)/(date_next - date_prev);
//
//	double interpolated_libor = coeff_1*libor_prev + coeff_2*libor_next;
//
//	//-- Update vectors of date and values
//	x.insert(x.begin()+index_interp,x_interp);
//	y.insert(y.begin()+index_interp,interpolated_libor);
//}
//
//
//double Interpolation::linearInterpolation(double x1, 
//			                              double x2, 
//								          double y1, 
//								          double y2, 
//								          double x_interp)
//{
//	double coeff_1 = (x2 - x_interp)/(x2 - x1);
//	double coeff_2 = (x_interp - x1)/(x2 - x1);
//	double res = coeff_1*y1 + coeff_2*y2;
//	return res;
//}
//
//
//void Interpolation::testLinearInterpolation()
//{
//	std::vector<double> someVector(3);
//	someVector[0] = 0.01;  
//	someVector[1] = 0.02; 
//	someVector[2] = 0.03;
//
//	std::vector<double> falseTenorDates(3);
//	falseTenorDates[0] = 0.;
//	falseTenorDates[1] = 0.5;
//	falseTenorDates[2] = 1.;
//
//	double maturity_date = 0.75; 
//	
//	double coeff_1 = (falseTenorDates[2]-maturity_date)/(falseTenorDates[2]-falseTenorDates[1]);
//	double coeff_2 = (maturity_date-falseTenorDates[1])/(falseTenorDates[2]-falseTenorDates[1]);
//	double expectedResult = coeff_1*someVector[1] + coeff_2*someVector[2];
//
//	NumericalTools::Interpolation interpolator;
//	interpolator.linearInterpolation(someVector,falseTenorDates,maturity_date);
//	for each (double inter_val in someVector)
//		std::cout << inter_val << " ";
//
//	std::cout << std::endl;
//	std::cout << "Expected result : " << expectedResult << std::endl;
//}