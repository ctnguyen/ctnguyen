
#include <LMM/numeric/Interpolation.h>

#include <iostream>
#include <algorithm>


namespace numeric
{

void Interpolation::linearInterpolation
			(
			std::vector<double>& y,
			std::vector<double>& x,
			const double&        x_interp
			)
{
	
	if (x_interp < x[0] || x_interp > x[x.size()-1])
	{
		throw("Interpolation.cpp ----> Error: invalid absciss input");
	}
	//-- Search the libor maturities bounding maturity_date
	size_t index_interp = 0;
	for (size_t i = 0; i < x.size(); ++i) 
	{
		if (x_interp > x[i])
			index_interp++;
	}

	//-- Set the dates before and after maturity_date
	double date_prev = x[index_interp-1];
	double date_next = x[index_interp];

	//-- Search in the libor matrix for libors corresponding to the previous dates
	double libor_prev =  y[index_interp-1];
	double libor_next = y[index_interp];

	double coeff_1 = (date_next - x_interp)/(date_next - date_prev);
	double coeff_2 = (x_interp - date_prev)/(date_next - date_prev);

	double interpolated_libor = coeff_1*libor_prev + coeff_2*libor_next;

	//-- Update vectors of date and values
	x.insert(x.begin()+index_interp,x_interp);
	y.insert(y.begin()+index_interp,interpolated_libor);
}


double Interpolation::linearInterpolation
			(
			const double& x1, 
			const double& x2, 
			const double& y1, 
			const double& y2, 
			const double& x_interp
			)
{
	double coeff_1 = (x2 - x_interp)/(x2 - x1);
	double coeff_2 = (x_interp - x1)/(x2 - x1);
	double res = coeff_1*y1 + coeff_2*y2;
	return res;
}


} //end namespace numerica