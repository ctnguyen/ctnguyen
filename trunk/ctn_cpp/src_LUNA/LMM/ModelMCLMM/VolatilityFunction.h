#ifndef LMM_MODEL_VOLATILITY_FUNCTION_H
#define LMM_MODEL_VOLATILITY_FUNCTION_H
#pragma once

#include <boost/shared_ptr.hpp>
#include <LMM/helper/LMMTenorStructure.h>


/*! \class VolatilityFunction
 *  Abstract class for modelling Volatility in the LMM model
 *
 *
 */
class VolatilityFunction
{
public:
	// f(t,i) = f_i(t) vol function for libor_i, a deterministic function of time
	//virtual double operator()(double t, size_t index) = 0; 
	//virtual double operator()(size_t indexLibor, size_t indexTime) = 0.0;

	VolatilityFunction(LMMTenorStructure_PTR lmmTenorStructure) : lmmTenorStructure_(lmmTenorStructure){}

	virtual double varIntegral( size_t indexTime_i, size_t indexTime_j, size_t indexLibor) const 
	{
		return covIntegral(indexTime_i,indexTime_j,indexLibor,indexLibor);
	}
	
	//! getter
	LMMTenorStructure_PTR get_LMMTenorStructure() const {return lmmTenorStructure_;}

	//! \int_{T_i}^{T_j} \sigma_{Li}(u)*\sigma_{Lj}(u) du
	virtual double covIntegral
		(
		size_t indexTime_i,
		size_t indexTime_j,
		size_t indexLibor_i,
		size_t indexLibor_j
		) const = 0;
		
	virtual void print(const std::string& filename) const = 0;

protected:

	LMMTenorStructure_PTR lmmTenorStructure_;

};

typedef boost::shared_ptr<VolatilityFunction>   VolatilityFunction_PTR;  // is it useful ? 


//! YY TODO: make this function more general: calculate covariance for whatever time interval.
//           so at least make it possible to use piecewise linear vol.
//! YY TODO:  to put these class in different class.

#endif /* LMM_MODEL_VOLATILITY_FUNCTION_H */