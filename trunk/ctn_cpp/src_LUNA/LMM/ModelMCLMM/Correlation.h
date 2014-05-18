#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

#include <boost/shared_ptr.hpp>

#include <LMM/ModelMCLMM/PCA.h>
#include <LMM/ModelMCLMM/RobonatoAngle.h>

using namespace std;
using namespace QuantLib;

//! YY TODO: need to do the check: the finally approximated matrix: B*B^T is positively defined!
//           what happens if the matrix is not positively defined ? ----  it's not a correlation matrix.

// ------------------------------------------------------------------------------
//
//                             Correlation
//
// ------------------------------------------------------------------------------
namespace CorrelationReductionTyype
{
	enum CorrelationReductionTyype {RA, PCA}; // RA: RobonatoAngle
}
class Correlation
{
protected:
	size_t fullRank_;                   // rank of correlation matrix.
	size_t reducedRank_;                // rank of the reduced correlation matrix 
	Matrix originalCorrelMatrix_;       // originalCorrelMatrix, size = (fullRank_, fullRank_)
	Matrix reducedCorrelMatrixB_;       // size = (fullRank_,reducedRank_)
	Matrix reducedCorrelMatrixApprox_ ; // approximate the originalCorrelMatrix, value = B*B^T, size = (rank_, rank_)
	CorrelationReductionTyype::CorrelationReductionTyype& reductionType_;

	bool   flagApproxConstruced_;

public:
	Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType); // YY: TODO don't like default parameter: use boost::defaultable<size_t> for reduceRank latter.
		
	void calculate();  // orignalCorrel -> B -> approxiCorrel = B*B^T

private:
	void calculateCorrelOriginal();
	void calculateReducedCorrelB();
	void calculateReducedCorrelApprox();
	virtual double correlOriginal(size_t i, size_t j) = 0; // YY Question: can the pure virtual function be private ? 

public:
	//! getter.
	size_t get_fullRank();
	size_t get_reducedRank();
	const Matrix& get_originalCorrelMatrix() const;
	const Matrix& get_reducedCorrelMatrixB() const;
	const Matrix& get_reducedCorrelMatrixApprox() const;
	const CorrelationReductionTyype::CorrelationReductionTyype& get_reductionType() const;
	const std::string get_reductionTypeString() const;
	bool  get_flagApproxConstruced()const;
	double correlApprox(size_t i, size_t j) const ;

	//print
	void print() const;
	void print_details(string& fileName) const;	

};
typedef boost::shared_ptr<Correlation> Correlation_PTR;


// ------------------------------------------------------------------------------
//
//                          Shosemaker2_Correlation
//
// ------------------------------------------------------------------------------
class Shosemaker2_Correlation : public Correlation
{
private:
	double eta_;
	double rhoInfty_;

public:
	Shosemaker2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType, double eta, double rhoInfty); // // YY: TODO don't like default parameter: use boost::defaultable<size_t> for reduceRank latter.
	bool checkParams();

private:
	double correlOriginal(size_t index_i, size_t index_j); 
};


// ------------------------------------------------------------------------------
//
//                          Shosemaker3_Correlation
//
// ------------------------------------------------------------------------------
//! YY  the formula is not sure correct: result is different from the X-report ??? !!! ---- TOCHECK 
class Shosemaker3_Correlation : public Correlation
{
private:
	double eta1_;
	double eta2_;
	double rhoInfty_;

public:
	Shosemaker3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType, double eta1, double eta2, double rhoInfty);
	bool checkParams();

private:
	double correlOriginal(size_t index_i, size_t index_j); 
};	



// ------------------------------------------------------------------------------
//
//                          Robonato2_Correlation
//
// ------------------------------------------------------------------------------
class Robonato2_Correlation : public Correlation
{
private:
	double beta_;
	double rhoInfty_;

public:
	Robonato2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType, double beta, double rhoInfty);
	bool checkParams();
private:
	double correlOriginal(size_t index_i, size_t index_j); 
};	



// ------------------------------------------------------------------------------
//
//                          Robonato3_Correlation
//
// ------------------------------------------------------------------------------
class Robonato3_Correlation : public Correlation
{
private:
	double alpha_;
	double beta_;
	double rhoInfty_;

public:
	Robonato3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType, double alpha, double beta, double rhoInfty);

	bool checkParams();

private:
	double correlOriginal(size_t index_i, size_t index_j); 
};	




// ------------------------------------------------------------------------------
//
//                          XY_beta_Correlation
//
// ------------------------------------------------------------------------------
class XY_beta_Correlation : public Correlation
{
private:
	double alpha_;
	double beta_;

public:
	XY_beta_Correlation  (size_t fullRank, 
						  size_t reducedRank, 
						  CorrelationReductionTyype::CorrelationReductionTyype& reductionType,
						  double alpha, 
						  double beta);

	bool checkParams();

private:
	double correlOriginal(size_t index_i, size_t index_j); 
};	


// ------------------------------------------------------------------------------
//
//                          Const_Correlation
//
// ------------------------------------------------------------------------------
//! used for perfectly correlated & independent correlation structure.
class Const_Correlation : public Correlation
{
private:
	double correlConst_;

public:
	Const_Correlation  (size_t fullRank, 
		size_t reducedRank, 
		CorrelationReductionTyype::CorrelationReductionTyype& reductionType,
		double correlConst);

	bool checkParams();

private:
	double correlOriginal(size_t index_i, size_t index_j); 

};	
