#ifndef LMM_MODEL_DISPERSION_H
#define LMM_MODEL_DISPERSION_H
#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <LMM/helper/LMMTenorStructure.h>
#include <LMM/ModelMCLMM/Correlation.h>
#include <LMM/ModelMCLMM/VolatilityFunction.h>


//! YY: suppose correlation is time dependent, so can separate: Correlation & Vol 

/*! \class Dispersion 
 *  Modelize the structure of volatility
 *
 */
class Dispersion 
{

public:

	Dispersion(Correlation_PTR correlation_, VolatilityFunction_PTR volatilityFunction);

	virtual ~Dispersion(){}

	//! int_{T_indexTime_i}^{T_indexTime_j} <vol_{indexLibor_i},vol_{indexLibor_j}>(u) du, 
	double covIntegral( size_t indexTime_i,
						size_t indexTime_j,
						size_t indexLibor_i,
						size_t indexLibor_j) const;

	double varIntegral( size_t indexTime_i,
						size_t indexTime_j,
						size_t indexLibor) const;

	// getter
	size_t getNbFactors() const { return nbFactor_ ; }
	size_t get_horizon()  const { return lmmTenorStructure_->get_horizon() ; }

	const        Correlation_PTR& get_CorrelationPtr()        const { return correlation_        ; }
	const  LMMTenorStructure_PTR& get_lmmTenorStructure()     const { return lmmTenorStructure_  ; }
	const VolatilityFunction_PTR& get_VolatilityFunctionPtr() const { return volatilityFunction_ ; }


protected:

	const size_t nbFactor_;                            // comes from correlation_.reducedRank
	LMMTenorStructure_PTR lmmTenorStructure_;        // comes from volatility .
	Correlation_PTR correlation_;  
	VolatilityFunction_PTR volatilityFunction_;  
};

typedef  boost::shared_ptr<Dispersion>  Dispersion_PTR;

#endif /* LMM_MODEL_DISPERSION_H */