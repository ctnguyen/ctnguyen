#pragma once

//#include "Interpolation.h"
//#include "MarketInfoCollector.h"

//#include "Dispersion.h"
//#include "McGenerator.h"
//#include "Name.h"
//#include "LMMTenorStructure.h"
//#include "Dispersion.h"

#include <LMM/helper/RNGenerator.h>
#include <LMM/ModelMCLMM/Lmm.h>


//#include <vector>
//#include <boost/numeric/ublas/io.hpp>
//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/shared_ptr.hpp>

//#include <cassert>  // for assert

//class Tensor
//{
//	typedef boost::numeric::ublas::matrix<double> matrix;
//    std::vector<matrix> tensor_; // tensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k], k=[1,...,N], i,j=[k,...,N]
//public:
//
//	Tensor(size_t size1, size_t size2, size_t size3)
//		:tensor_(size1, matrix(size2, size3)){}
//
//	double & operator()(size_t index_T, size_t indexLibor_i, size_t indexLibor_j)
//	{
//		//! YY Attention: This is a special condition for My LMM implementation, not general tensor condition.
//		//! YY TODO: remove this check when the code is stable.
//		assert(index_T >=1 && indexLibor_i>=index_T && indexLibor_j >= index_T);
//		return tensor_[index_T](indexLibor_i, indexLibor_j);
//	}
//
//	//! getter ans setter
//	const std::vector<matrix>& get_tensor() const { return tensor_; }
//	void set_ensor(std::vector<matrix> val) { tensor_ = val;}
//	const matrix& operator[](size_t indexT) const
//	{ 
//		assert(indexT >=1);
//		return tensor_[indexT];
//	}
//
//};

namespace MCSchemeType
{
	enum MCSchemeType{ EULER, PC, IPC}; // Euler, predictor-corrector, improved predictor corrector (more fast)
	std::string mcSchemeType2String(MCSchemeType mcSchemeType);
}

typedef boost::numeric::ublas::matrix<double> matrix;


class McLmm : public Lmm
{
protected:
	//! YY exist in Dispersion, but only for the simplicity of writing the code, put them here.
	size_t nbFactor_;   // = 3
	size_t horizon_;    // N: max Libor
	Matrix B_; 


	//! comes from simulation
	std::vector<double> numeraires_; // numeraire[i] = P(T_i,T_{N+1})  , size = N+1  
	matrix liborMatrix_;             // liborMatrix_(i,j) = L_i(T_j)   , size = (N+1,N+1), first row&column not useful.
	RNGenerator_PTR rnGenerator_;
	MCSchemeType::MCSchemeType    mcSchemeType_;
	//! static Test
	//matrix cumulated_drifts_;
	//matrix cumulated_squared_drifts_;
	//matrix cumulated_omega_coef_;  

public:

	//McLmm();

	McLmm(const Dispersion&                  dispersion,
		  const std::vector<double>&         shifts,           // size = N+1
		  const std::vector<double>&         liborsInitValue,  // size = N+1
		  RNGenerator_PTR                    rnGenerator,      
		  MCSchemeType::MCSchemeType		 mcSchemeType);

	//McLmm(const McLmm & myLmm);

	//~McLmm();

	//! YY: TODO: for the moment suppose simulation step = delta_T, so: only need to pre-calculate 3D covarianceTensor.
	//            When need longStepping or more fine step, should modify this structure.
	//! tensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k]
    //                  k = [1,...,N], i,j = [k,...,N]
	//void initCovarianceTensor();

	//! diffusion integration.
	//! int_{T_{k-1}}^{T_k} sigma_i(t) dW_t,   indexTime = k
	Real McLmm::computeIntSto(size_t indexTime, 
		size_t indexLibor, 
		const std::vector<double>& G);

	virtual void simulateLMM()         =0;
	virtual void computeNumeraires()   =0;
	
	void initLiborMatrix(const std::vector<double>& libors_init);

	//-- Getters 
	//size_t get_horizon() {return horizon_;}
	//const LMMTenorStructure& get_LMMTenorStructure () const {return dispersion_.get_lmmTenorStructure();}
	//const std::vector<double>& get_shifts()			  const {return shifts_;}
	const matrix& get_liborMatrix()                   const {return liborMatrix_;}
	const std::vector<double>& get_numeraire()		  const {return numeraires_;}
	double get_numeraire(size_t index)				  const {return numeraires_[index];}
	MCSchemeType::MCSchemeType  get_mcSchemeType()    const{return mcSchemeType_;}
	RNGenerator_PTR get_RNGenerator() {return rnGenerator_;}  //! needed when resetSeed

	////-- Setters 
	//void set_shifts(const std::vector<double>& shifts);

	//!
	virtual void print() const;
};

typedef boost::shared_ptr<McLmm> MCLmm_PTR;
