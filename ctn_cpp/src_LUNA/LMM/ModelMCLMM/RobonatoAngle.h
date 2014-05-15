#pragma once

//! YY shit should not include so much file in .h, should not use namespace QuantLib in .h !!!! 


//#include <ql/errors.hpp>  // for QL_REQUIRE


//"Parameterizing correlations: a geometric interpretation"
#include <string>
#include <fstream>
#include <math.h>
#include <cassert>

#include <boost/function.hpp>

#include <ql/math/optimization/costfunction.hpp>
#include <ql/math/array.hpp>
#include <ql/math/matrix.hpp>
#include <ql/utilities/disposable.hpp>

//using namespace QuantLib;

//! YY not efficient at all, memory usage or algorithm. need to improve.
//! all angles in [0,pi] expect esp angles \in [0,2*pi]
class RobonatoAngle
{
	size_t   matrixSize_;   // fullRank
	size_t   rank_;         // reducecRank: >=2
	QuantLib::Array  angles_;       // valide range [0,PI] and for specailAngle [0,2*PI]
	QuantLib::Matrix BMatrix_;      // size = (matrixSize_, rank_)
	QuantLib::Matrix correlMatrix_; // correlMatrix_ = BMatrix_*BMatrix_^T

public:
	//! default constructor: does nothing. 
	RobonatoAngle(){};

	//! construct the matrix from Robonato Angle
	RobonatoAngle(size_t matrixSize, size_t rank, const QuantLib::Array& angles); // Angle -> BMatrix, correlMatrix

	//! construct the matrix from Robonato Angle
	RobonatoAngle(const QuantLib::Matrix& BMatrix);// BMatrix -> Angle, correlMatrix

	//! given the originalCorrelMatrix then find the nearest approximation RobonatoAngle
	RobonatoAngle(const QuantLib::Matrix& originalCorrelMatrix, size_t reducedRank);  // the finally saved correlMatrix_ is not the originalCorrelMatrix.


	void calculateBMatrixFromAngle(const QuantLib::Array& angles);
	void calculateAngleFromBMatrix(const QuantLib::Matrix& BMatrix);

	QuantLib::Array  get_angles() const {return angles_;}
	QuantLib::Matrix get_BMatrix() const {return BMatrix_;}
	QuantLib::Matrix get_correlMatrix() const {return correlMatrix_;}

	bool isSpecialAnlge(size_t index_i) const;

	bool checkAngle(const QuantLib::Array& angles) const;

	//! all angles in [0,pi] expect esp angles \in [0,2*pi]
	static bool isSpecialAnlge(size_t index_i, size_t rank)
	{
		if(rank<2)
			throw("rank too small, not permitted");
		if(index_i ==0) 
			return false;
		size_t r = rank-1; 

        if((index_i+1)%r==0)
			return true;
		else
			return false;
	}


	//! nearest Matrix to originalCorrelMatrix
	void solveTheNearestCorrelProblem(const QuantLib::Matrix& target); // given: correlMatrix_ -> try to find its nearest approximation by RobonatoAngle


	void print_details(std::string& fileName) const;


	// YY Duplicate: RobonatoAngle::calculateBMatrixFromAngle(const Array& angles)
	static QuantLib::Disposable<QuantLib::Matrix> triangularAnglesParametrizationYY( const QuantLib::Array& angles,
															   size_t matrixSize,
															   size_t rank)
	{
		// what if rank == 1?
		//QL_REQUIRE((rank-1) * (matrixSize ) == angles.size(),
		//			"rank-1) * (matrixSize ) == angles.size()");

		assert((rank-1) * (matrixSize ) == angles.size());

		QuantLib::Matrix BMatrix(matrixSize, rank);

		size_t k = 0; //angles index
		for (size_t i=0; i<matrixSize; ++i) {
			double sinProduct = 1.0;
			for (size_t j=0; j<rank-1; ++j) {
				BMatrix[i][j] = std::cos(angles[k]);
				BMatrix[i][j] *= sinProduct;
				sinProduct *= std::sin(angles[k]);
				++k;
			}
			BMatrix[i][rank-1] = sinProduct;
		}
		return BMatrix;
	}


	
    //! for optimization
    // Cost function associated with Frobenius norm.
    // <http://en.wikipedia.org/wiki/Matrix_norm>
    class FrobeniusCostFunctionYY : public QuantLib::CostFunction
	{
      public:
        FrobeniusCostFunctionYY(const QuantLib::Matrix& target,
						        const boost::function<QuantLib::Disposable<QuantLib::Matrix>(const QuantLib::Array&,
																	   size_t,
																	   size_t)>& f,
							  size_t matrixSize,
							  size_t rank)
        : target_(target), f_(f), matrixSize_(matrixSize), rank_(rank) {}
        double value (const QuantLib::Array &x) const;
        QuantLib::Disposable<QuantLib::Array> values (const QuantLib::Array &x) const;
      private:
        QuantLib::Matrix target_;
        boost::function<QuantLib::Disposable<QuantLib::Matrix>(const QuantLib::Array&, size_t, size_t)> f_;
        size_t matrixSize_;
        size_t rank_;
    };

};



//! function of test
void testSpecialAngles();

void testRobonatoAngle();