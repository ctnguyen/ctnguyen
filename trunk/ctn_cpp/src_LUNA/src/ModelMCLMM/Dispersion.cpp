#include "Dispersion.h"
#include <cassert>

Dispersion::Dispersion(Correlation_PTR correlation,
					   VolatilityFunction_PTR volatilityFunction)
					   :nbFactor_(correlation->get_reducedRank()),
					    lmmTenorStructure_(volatilityFunction->get_LMMTenorStructure()),
					    correlation_(correlation),
					    volatilityFunction_(volatilityFunction)
{
	assert(correlation_->get_fullRank() == lmmTenorStructure_.get_horizon()+1);
	if(!correlation_->get_flagApproxConstruced())
		correlation_->calculate();
}


//! YY: TODO make it more efficient, covIntegral(.) recalculate lots of thing. can use pre-calculation here.
//           but the problem doesn't seems so grave, because of the pre-calculation in MC pricer.
double Dispersion::covIntegral(size_t indexTime_i,
							   size_t indexTime_j,
							   size_t indexLibor_i,
							   size_t indexLibor_j)
{
	return correlation_->correlApprox(indexLibor_i,indexLibor_j) * volatilityFunction_->covIntegral(indexTime_i, indexTime_j, indexLibor_i, indexLibor_j);
}

double Dispersion::varIntegral( size_t indexTime_i,
							   size_t indexTime_j,
							   size_t indexLibor)
{
	return covIntegral( indexTime_i,
						indexTime_j,
						indexLibor,
						indexLibor);
}
