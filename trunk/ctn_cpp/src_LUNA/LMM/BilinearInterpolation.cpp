//#include "BilinearInterpolation.h"
//
///*BilinearInterpolation::BilinearInterpolation(const std::vector<double>& x1, 
//											 const std::vector<double>& x2,
//											 const matrix_& y)
//											 : m_(x1.size()),n_(x2.size()),y_(y)
//{}  */  
//
//BilinearInterpolation::BilinearInterpolation()
//{}
//
//double BilinearInterpolation::interpolate(double xp, double yp,
//										  double x1, double x2,
//										  double y1, double y2,
//										  double a, double b,
//										  double c, double d)
//	                                      
//{
//	/*NumericalTools::Interpolation interpolator;
//	double f_ab = interpolator.linearInterpolation(x1,x2,a,b,xp);
//	double f_cd = interpolator.linearInterpolation(x1,x2,c,d,xp);
//	double fp = interpolator.linearInterpolation(y1,y2,f_ab,f_cd,yp);*/
//
//	double t = (xp-x1)/(x2-x1);
//	double u = (yp-y1)/(y2-y1);
//
//	double res = (1-t)*(1-u)*a + t*(1-u)*b + t*u*c + (1-t)*u*d;
//	return res;
//} 