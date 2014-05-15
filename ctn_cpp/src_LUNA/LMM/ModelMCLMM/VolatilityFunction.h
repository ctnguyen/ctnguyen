#pragma once
#include <boost/shared_ptr.hpp>
#include <LMM/ModelMCLMM/LMMTenorStructure.h>

//! YY TODO: make this function more general: calculate covariance for whatever time interval.
//           so at least make it possible to use piecewise linear vol.

//#include <boost/numeric/ublas/triangular.hpp>  // Triangular matrix
//#include <boost/numeric/ublas/io.hpp>

//#include "LMMTenorStructure.h""

//! YY TODO:  to put these class in different class.
class VolatilityFunction
{
protected:
	LMMTenorStructure   lmmTenorStructure_;
public:
	// f(t,i) = f_i(t) vol function for libor_i, a deterministic function of time
	//virtual double operator()(double t, size_t index) = 0; 
	//virtual double operator()(size_t indexLibor, size_t indexTime) = 0.0;

	VolatilityFunction(const LMMTenorStructure& lmmTenorStructure)
		:lmmTenorStructure_(lmmTenorStructure){}

	
	//! int_{T_indexTime_i}^{T_indexTime_j} vol_{indexLibor_i}(u)*vol_{indexLibor_j}(u) du, 
	virtual double covIntegral( size_t indexTime_i,
								size_t indexTime_j,
								size_t indexLibor_i,
								size_t indexLibor_j) = 0;

	virtual double varIntegral( size_t indexTime_i,
								size_t indexTime_j,
								size_t indexLibor) 
	{
		return covIntegral( indexTime_i,
							indexTime_j,
							indexLibor,
							indexLibor);
	}

	//! getter
	const LMMTenorStructure& get_LMMTenorStructure() const {return lmmTenorStructure_;}

	virtual void print() const = 0;
};
typedef boost::shared_ptr<VolatilityFunction>   VolatilityFunction_PTR;  // is it useful ? 


