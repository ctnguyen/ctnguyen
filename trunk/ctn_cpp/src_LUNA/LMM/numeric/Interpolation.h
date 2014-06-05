#ifndef LMM_NUMERIC_INTERPOLATION_H
#define LMM_NUMERIC_INTERPOLATION_H
#pragma once

#include <vector>

namespace numeric 
{

	class Interpolation
	{
	public:
		//-- Interpolation on y - find value corresponding to given maturity date
		// Insert a point in the appropriated position in x vector
		// Compute the coherent point in vector y, and insert it into the appropriated position 
		void linearInterpolation
			(
			std::vector<double>& y,
			std::vector<double>& x,
			const double&        x_interp
			);

		double linearInterpolation
			(
			const double& x1, 
			const double& x2, 
			const double& y1, 
			const double& y2, 
			const double& x_interp
			);

	};
}
#endif /* LMM_NUMERIC_INTERPOLATION_H */