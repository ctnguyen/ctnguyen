//#pragma once
//
//#include <vector>
//#include "Interpolation.h"
//
//typedef std::vector<std::vector<double>> matrix_;
//
//
//class BilinearInterpolation
//{
//private:
//	//NumericalTools::Interpolation linearInterpolator_;   
//	//size_t m_, n_;                                         //-- sizes
//	//matrix_ y_;                                         //-- matrix to be interpolated
//
//public:
//	//BilinearInterpolation(const std::vector<double>& x1, // first dim vector
//	//	                  const std::vector<double>& x2, // second dim vector
//	//					  const matrix_& y);             
//
//	BilinearInterpolation();
//
//	//-- Must give the four inputs from lower left, then lower right, ... 
//	double interpolate(double xp, double yp, // interpolation on coordinates (xp,yp)
//		               double x1, double x2,
//					   double y1, double y2,
//					   double a, double b,
//					   double c, double d);
//};
//
