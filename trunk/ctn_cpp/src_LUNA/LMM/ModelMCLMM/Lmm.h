#pragma once

#include <vector>
#include <cassert>  // for assert

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>


//#include "Interpolation.h"
//#include "MarketInfoCollector.h"
#include <LMM/Name.h>
#include <LMM/helper/RNGenerator.h>
#include <LMM/ModelMCLMM/Dispersion.h>
#include <LMM/ModelMCLMM/LMMTenorStructure.h>



class Tensor
{
	typedef boost::numeric::ublas::matrix<double> matrix;
    std::vector<matrix> tensor_; // tensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k], k=[1,...,N], i,j=[k,...,N]
public:

	Tensor(size_t size1, size_t size2, size_t size3)
		:tensor_(size1, matrix(size2, size3)){}

	double & operator()(size_t index_T, size_t indexLibor_i, size_t indexLibor_j) 
	{
		//! YY Attention: This is a special condition for My LMM implementation, not general tensor condition.
		//! YY TODO: remove this check when the code is stable.
		assert(index_T >=1 && indexLibor_i>=index_T && indexLibor_j >= index_T);
		return tensor_[index_T](indexLibor_i, indexLibor_j);
	}

	//! getter ans setter
	const std::vector<matrix>& get_tensor() const { return tensor_; }
	void set_ensor(std::vector<matrix> val) { tensor_ = val;}
	const matrix& operator[](size_t indexT) const
	{ 
		assert(indexT >=1);
		return tensor_[indexT];
	}

};

typedef boost::numeric::ublas::matrix<double> matrix;

class Lmm 
{
protected:
	Dispersion			dispersion_;
	std::vector<double> shifts_;                 
	Tensor				covarianceTensor_;           // tensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k]
	Tensor				cumulatedCovarianceTensor_;  // tensor_(k,i,j): L_i, L_j 's integral of vol in [T_0,T_k] // usefor approxSwaption Pricing
	std::vector<double> liborsInitValue_;

public:
	Lmm(  const Dispersion&                  dispersion,
		  const std::vector<double>&         shifts,           // size = N+1
		  const std::vector<double>&         liborsInitValue)
		  :dispersion_(dispersion), 
		   shifts_(shifts), 
		   covarianceTensor_         (dispersion_.get_horizon()+1, dispersion_.get_horizon()+1,dispersion_.get_horizon()+1),
		   cumulatedCovarianceTensor_(dispersion_.get_horizon()+1, dispersion_.get_horizon()+1,dispersion_.get_horizon()+1),
		   liborsInitValue_(liborsInitValue)
	{
		initCovarianceTensor();
		initCumulatedCovarianceTensor();
	}


	//! YY: TODO: for the moment suppose simulation step = delta_T, so: only need to pre-calculate 3D covarianceTensor.
	//            When need longStepping or more fine step, should modify this structure.
	//! covarianceTensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k]
    //							  k = [1,...,N], i,j = [k,...,N]
	void initCovarianceTensor();
	void initCumulatedCovarianceTensor();

	//! Getter
	//! information contained in Dispersion
	size_t get_horizon() const {return dispersion_.get_horizon();}
	const LMMTenorStructure&   get_LMMTenorStructure () const {return dispersion_.get_lmmTenorStructure();}


	const std::vector<double>& get_shifts()			  const {return shifts_;}
	const std::vector<double>& get_liborsInitValue()  const {return liborsInitValue_;}

	double get_covarianceTensor(size_t indexTime, size_t indexLibor_i, size_t indexLibor_j) ; // YY TODO: add const
	double get_cumulatedcovarianceTensor(size_t indexTime, size_t indexLibor_i, size_t indexLibor_j) ; // YY TODO: add const 


};

typedef boost::shared_ptr<Lmm> Lmm_PTR;
