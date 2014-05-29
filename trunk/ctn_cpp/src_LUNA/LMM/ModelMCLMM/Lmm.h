#pragma once

#include <vector>
#include <cassert>  // for assert

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>

#include <LMM/Name.h>
#include <LMM/helper/RNGenerator.h>
#include <LMM/ModelMCLMM/Dispersion.h>
#include <LMM/ModelMCLMM/LMMTenorStructure.h>


typedef boost::numeric::ublas::matrix<double> matrix;

/*! The tensor is a 3D matrix storing for precomputed value of time integral in each intervall [T_{k-1},T_k]
 *  Each case stored 
 *
 * tensor(k,i,j) = \int_{T_{k-1}}^{T_k}  vol_i(t) * vol_j(t)  * \rho_{ij} dt
 *
 * Where
 * vol_i, vol_j are volatilities for i-th and j-th LIBOR path : L_i,L_j
 * \rho_{ij} is the reduced approximated correlation matrix (same dimension, but reduced for the nb factor)
 */
class Tensor
{

public:

	Tensor(size_t size1, size_t size2, size_t size3);

	void set_tensor(std::vector<matrix> val) ;

	double & operator()(size_t index_T, size_t indexLibor_i, size_t indexLibor_j)             ;
	const double & operator()(size_t index_T, size_t indexLibor_i, size_t indexLibor_j) const ;

	const std::vector<matrix>& get_tensor() const ;
	
	const matrix& operator[](size_t indexT) const ;		

private:
    std::vector<matrix> tensor_; // tensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k], k=[1,...,N], i,j=[k,...,N]
};

class Lmm 
{
public:
	Lmm(  const Dispersion&                  dispersion,
		  const std::vector<double>&         shifts,           // size = N+1
		  const std::vector<double>&         liborsInitValue);


	//! YY: TODO: for the moment suppose simulation step = delta_T, so: only need to pre-calculate 3D covarianceTensor.
	//            When need longStepping or more fine step, should modify this structure.
	//! covarianceTensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k]
    //							  k = [1,...,N], i,j = [k,...,N]
	void initCovarianceTensor();
	void initCumulatedCovarianceTensor();

	//! Getter
	//! information contained in Dispersion
	size_t                             get_horizon() const ; //{return dispersion_.get_horizon();}
	ConstLMMTenorStructure  get_LMMTenorStructure () const ; //{return dispersion_.get_lmmTenorStructure();}
	
	const std::vector<double>&          get_shifts() const ; //{return shifts_;}
	const std::vector<double>& get_liborsInitValue() const ; //{return liborsInitValue_;}

	const double& get_covarianceTensor(size_t indexTime, size_t indexLibor_i, size_t indexLibor_j)          const ; 
	const double& get_cumulatedcovarianceTensor(size_t indexTime, size_t indexLibor_i, size_t indexLibor_j) const ;

protected:
	Dispersion			dispersion_               ;
	std::vector<double> shifts_                   ;                 
	Tensor				covarianceTensor_         ;  // tensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k]
	Tensor				cumulatedCovarianceTensor_;  // tensor_(k,i,j): L_i, L_j 's integral of vol in [T_0,T_k] // usefor approxSwaption Pricing
	std::vector<double> liborsInitValue_          ;
};

typedef boost::shared_ptr<Lmm> Lmm_PTR;
