#include "Lmm.h"
#include <cassert>
void Lmm::initCovarianceTensor()
{
	//! YY TODO: make the not initialized value to #IND

	// tensor_:  k,i,j
	// L_i, L_j 's integral of vol in [T_{k-1},T_k]: i,j >= k
	size_t horizon = dispersion_.get_horizon();
	for(size_t indexTime = 1; indexTime <= horizon; ++indexTime)
	{
		for(size_t indexLibor_i = indexTime; indexLibor_i <= horizon; ++indexLibor_i)
		{
			for(size_t indexLibor_j = indexLibor_i; indexLibor_j <= horizon; ++indexLibor_j)
			{
				covarianceTensor_(indexTime, indexLibor_i, indexLibor_j) = dispersion_.covIntegral(indexTime-1,
					indexTime,
					indexLibor_i,
					indexLibor_j);

				//! because of the symmetric of the tensor
				covarianceTensor_(indexTime, indexLibor_i, indexLibor_j) = covarianceTensor_(indexTime, indexLibor_i, indexLibor_j);

			}
		}
	}
}

double Lmm::get_covarianceTensor(size_t indexTime, size_t indexLibor_i, size_t indexLibor_j)  
{
	assert(indexTime <= indexLibor_i && indexTime <= indexLibor_j);
	return covarianceTensor_(indexTime, indexLibor_i, indexLibor_j);
}


void Lmm::initCumulatedCovarianceTensor()
{
	// tensor_:  k,i,j
	// L_i, L_j 's integral of vol in [T_0,T_k]: i,j >= k
	size_t horizon = dispersion_.get_horizon();
	for(size_t indexTime = 1; indexTime <= horizon; ++indexTime)
	{
		for(size_t indexLibor_i = indexTime; indexLibor_i <= horizon; ++indexLibor_i)
		{
			for(size_t indexLibor_j = indexLibor_i; indexLibor_j <= horizon; ++indexLibor_j)
			{
				if(indexTime ==1)
				{
					cumulatedCovarianceTensor_(indexTime, indexLibor_i, indexLibor_j) = covarianceTensor_(indexTime, indexLibor_i, indexLibor_j);
				}
				else
				{
					cumulatedCovarianceTensor_(indexTime, indexLibor_i, indexLibor_j) =  cumulatedCovarianceTensor_(indexTime-1, indexLibor_i, indexLibor_j) + covarianceTensor_(indexTime, indexLibor_i, indexLibor_j);
				}
			}
		}
	}

}

double Lmm::get_cumulatedcovarianceTensor(size_t indexTime, size_t indexLibor_i, size_t indexLibor_j)  
{
	assert(indexTime <= indexLibor_i && indexTime <= indexLibor_j);
	return cumulatedCovarianceTensor_(indexTime, indexLibor_i, indexLibor_j);
}