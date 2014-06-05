#ifndef LMM_MODEL_HGVOLATILITY_FUNCTION_H
#define LMM_MODEL_HGVOLATILITY_FUNCTION_H
#pragma once

#include <boost/numeric/ublas/triangular.hpp>  // Triangular matrix
#include <boost/numeric/ublas/io.hpp>

#include <ql/termstructures/volatility/abcd.hpp>

#include <LMM/helper/LMMTenorStructure.h>
#include <LMM/ModelMCLMM/VolatilityFunction.h>


//! struct helper regrouping abcd parameters for abcd volatility model
struct AbcdParams 
{
	//abcdFunc(tau) = (a+ b*tau)*exp(-c*tau) + d;
	const double& a_; const double& b_; const double& c_; const double& d_;			
	
	AbcdParams(const double& a, const double& b, const double& c, const double& d);
};


/*! \class HGVolatilityFucntion
*
*
*
*/

class HGVolatilityFunction : public VolatilityFunction
{
	//! --------------------------------- h ------------------------------------
	//! h: ABCD function: totally Homogeneous, give the humped shape.
	//    same for every Libor.
public:

	class AbcdPWConstFunction  // regroup the QuantLib defined abcdFunction.
	{
	public:
		AbcdPWConstFunction(const AbcdParams& abcdParams, LMMTenorStructure_PTR lmmTenorStructure);

		//! getter
		const QuantLib::AbcdFunction& get_AbcdFunction() const ;

		//! return piecewise constant vol of   L_indexLibor in time interval: [T_{indexTime-1}, T_indexTime]
		double operator()(size_t indexLibor, size_t indexTime) const; // operator(i,j) --return vol--> hij, i>=j			
	
	private:
		LMMTenorStructure_PTR lmmTenorStructure_;
		QuantLib::AbcdFunction  abcdFunction_     ;    // homogeneous part, decide the hump shape. 
	};


	//! Constructor
	HGVolatilityFunction(const AbcdParams& abcdParams, LMMTenorStructure_PTR lmmTenorStructure);        // horizon = N, total number of Libor: L_k, k = [0,N]

	
	//! int_{T_indexTime_i}^{T_indexTime_j} vol_{indexLibor_i}(u)*vol_{indexLibor_j}(u) du, 
	double covIntegral( size_t indexTime_i,
		size_t indexTime_j,
		size_t indexLibor_i,
		size_t indexLibor_j) const;

	//! 
	void print(const std::string& filename) const;


private:
	const size_t        horizon_;
	AbcdPWConstFunction abcdPWConstFunction_;


	//! Add artificial: 1st row & column (should not call index [0] for row or column)!!! 

	//! triangular matrixSize = (horizon +1, horizon +1)
	//! instantaneous vol: piecewiseConstant, element(i,j) = vol of Libor_i in [T_j, T_{j-1}]
	boost::numeric::ublas::triangular_matrix<double, boost::numeric::ublas::lower> hPWConstFunc_;  
	boost::numeric::ublas::triangular_matrix<double, boost::numeric::ublas::lower> gPWConstFunc_;  

	//! YY TODO: to do optimization later ... 
	//! cumulated vol: the purpose is for the easy to retrieve the integrated vol in interval [T_i,T_j]:
	//! triangular matrixSize = (horizon +1, horizon +1)
	//! element(i,j) = vol of Libor_i in [T_0, T_j]
	//boost::numeric::ublas::triangular_matrix<double, lower> volCumulated_;  //! precalculated Vol

	//bool ifVolisUpToDate_; 
	
	void construct_hPWConstFunc();
	void construct_gPWConstFunc();

	//! Vol 
	//! i = indexLibor
	//! j = indexTime
	//! volatility of L_i at [T_{j-1},T_j]
	double operator()(size_t indexLibor, size_t indexTime) const; // operator(ij) --return vol--> hij, i>=j

	//! Whne t in [T_i,T_{i+1}], return index= i+1
	size_t indexSearch(const double& t) const;

};

typedef HGVolatilityFunction::AbcdPWConstFunction AbcdPWConstFunction;


//! The idea is to use h represent the humped shape (homogeneity), and then use function g to match the swaptionMatrix
//! YY: Currently it's piecewise Constant version: when implement other version, need to implement the heritage version. 
//! YY: TODO the implementation latter... 

#endif /* LMM_MODEL_HGVOLATILITY_FUNCTION_H */