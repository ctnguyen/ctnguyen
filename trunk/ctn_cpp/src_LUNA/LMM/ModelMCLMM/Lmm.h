#ifndef LMM_ModelMCLMM_LMM_H
#define LMM_ModelMCLMM_LMM_H
#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

#include <LMM/Name.h>
#include <LMM/helper/Tensor.h>
#include <LMM/helper/RNGenerator.h>
#include <LMM/helper/LMMTenorStructure.h>
#include <LMM/ModelMCLMM/Dispersion.h>



/*! \class Lmm
 *  Base class for all Lmm Model
 */
class Lmm 
{
public:

	//! constructor
	Lmm( const Dispersion          & dispersion     ,
		 const std::vector<double> & shiftsLibors   ,
		 const std::vector<double> & liborsInitValue);

	//! Getter, all are const
	size_t                             get_horizon() const ;
	LMMTenorStructure_PTR   get_LMMTenorStructure () const ;
	
	const std::vector<double>&          get_shifts() const ;
	const std::vector<double>& get_liborsInitValue() const ;

	//ctntodo here is not to get the Tensor, but only get the element, so rename get_covariance
	const double& get_covarianceTensor         (size_t indexTime, size_t indexLibor_i, size_t indexLibor_j) const ; 
	const double& get_cumulatedcovarianceTensor(size_t indexTime, size_t indexLibor_i, size_t indexLibor_j) const ;

	virtual void write_to_stream(std::ostream& outputstream) const ;

protected :

	Dispersion			dispersion_               ;
	std::vector<double> shifts_                   ;                 
	Tensor				covarianceTensor_         ;  // tensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k]
	Tensor				cumulatedCovarianceTensor_;  // tensor_(k,i,j): L_i, L_j 's integral of vol in [T_0,T_k] // usefor approxSwaption Pricing
	std::vector<double> liborsInitValue_          ;


private :
	//! YY: TODO: for the moment suppose simulation step = delta_T, so: only need to pre-calculate 3D covarianceTensor.
	//            When need longStepping or more fine step, should modify this structure.
	//! covarianceTensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k]
    //							  k = [1,...,N], i,j = [k,...,N]
	void initCovarianceTensor();
	void initCumulatedCovarianceTensor();
};

typedef boost::shared_ptr<Lmm> Lmm_PTR;

std::ostream& operator<<(std::ostream& os, const Lmm& lmm);

#endif /* LMM_ModelMCLMM_LMM_H */