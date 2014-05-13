#pragma once
#include <ql/termstructures/volatility/abcd.hpp>
//#include <boost/shared_ptr.hpp>


#include <boost/numeric/ublas/triangular.hpp>  // Triangular matrix
#include <boost/numeric/ublas/io.hpp>

#include "LMMTenorStructure.h"
#include "VolatilityFunction.h"


//! The idea is to use h represent the humped shape (homogeneity), and then use function g to match the swaptionMatrix



//! YY: Currently it's piecewise Constant version: when implement other version, need to implement the heritage version. 
//! YY: TODO the implementation latter... 
class HGVolatilityFunction : public VolatilityFunction
{
	//! --------------------------------- h ------------------------------------
	//! h: ABCD function: totally Homogeneous, give the humped shape.
	//    same for every Libor.
public:
	class AbcdPWConstFunction  // regroup the QuantLib defined abcdFunction.
	{
	public:
		struct AbcdParams
		{
			double a_;
			double b_;
			double c_;
			double d_;

			//abcdFunc(tau) = (a+ b*tau)*exp(-c*tau) + d;
			AbcdParams(double a, double b, double c, double d)
				:a_(a), b_(b), c_(c), d_(d){}

			std::vector<double> toVector() const 
			{
			    std::vector<double> v;
				v.reserve(4);
				v.push_back(a_);
				v.push_back(b_);
				v.push_back(c_);
				v.push_back(d_);
			    return v;
			}
		};
	private:
		AbcdParams			   abcdParam_;
		QuantLib::AbcdFunction abcdFunction_;  // homogeneous part, decide the hump shape. 
		LMMTenorStructure      lmmTenorStructure_;
	public:
		AbcdPWConstFunction(const AbcdParams& abcdParams, const LMMTenorStructure& lmmTenorStructure)
			:
			abcdParam_(abcdParams.a_, abcdParams.b_, abcdParams.c_, abcdParams.d_),
			abcdFunction_(abcdParams.a_,abcdParams.b_,abcdParams.c_,abcdParams.d_),
			lmmTenorStructure_(lmmTenorStructure)
		{};

		//! Attention: a very slow function.
		//! return piecewise constant vol of   L_indexLibor in time interval: [T_{indexTime-1}, T_indexTime]
		double operator()(size_t indexLibor, size_t indexTime) const; // operator(i,j) --return vol--> hij, i>=j

		//! getter
		const AbcdParams& get_AbcdParams() const {return abcdParam_;}
	};


private:
	size_t              horizon_;
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

public:
	//! Constructor
	HGVolatilityFunction::HGVolatilityFunction(const AbcdPWConstFunction::AbcdParams& abcdParams,  // h FunctionParam
											   const LMMTenorStructure& lmmTenorStructure);        // horizon = N, total number of Libor: L_k, k = [0,N]

private:
	void construct_hPWConstFunc();
	void construct_gPWConstFunc();

	//! Vol 
	//! i = indexLibor
	//! j = indexTime
	//! volatility of L_i at [T_{j-1},T_j]
	double operator()(size_t indexLibor, size_t indexTime) const; // operator(ij) --return vol--> hij, i>=j

public:

	//! int_{T_indexTime_i}^{T_indexTime_j} vol_{indexLibor_i}(u)*vol_{indexLibor_j}(u) du, 
	double covIntegral( size_t indexTime_i,
						size_t indexTime_j,
						size_t indexLibor_i,
						size_t indexLibor_j);

	//!getter
	const AbcdPWConstFunction::AbcdParams& get_AbcdParams() const {return abcdPWConstFunction_.get_AbcdParams();}

	//! 
	void print() const;
private:
	//! Whne t in [T_i,T_{i+1}], return index= i+1
	size_t indexSearch(double t);
};

typedef HGVolatilityFunction::AbcdPWConstFunction::AbcdParams AbcdParams;
typedef HGVolatilityFunction::AbcdPWConstFunction    AbcdPWConstFunction;


