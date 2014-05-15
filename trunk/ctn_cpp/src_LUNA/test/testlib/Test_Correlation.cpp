#include <ql/math/matrixutilities/symmetricschurdecomposition.hpp>

#include <LMM/ModelMCLMM/Correlation.h>
//-----------------------------------------------------------------------------------------------
//
//                                             Test 
//
//-----------------------------------------------------------------------------------------------
void test_Robonato2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
{
	double beta  = 0.1;
	double rhoInfty = 0.0158;

	Correlation* rb2_Correlation = new Robonato2_Correlation(fullRank, reducedRank, reductionType, beta, rhoInfty);
	rb2_Correlation->calculate();

	string fileName = "E:\\Robonato2_Correlation.csv";
	rb2_Correlation->print_details(fileName);

	delete rb2_Correlation;
}

void test_Robonato3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
{
	double alpha = -0.001;
	double beta  = 0.1;
	double rhoInfty = 0.0158;

	Correlation* rb3_Correlation = new Robonato3_Correlation(fullRank, reducedRank, reductionType, alpha, beta, rhoInfty);
	rb3_Correlation->calculate();

	string fileName = "E:\\Robonato3_Correlation.csv";
	rb3_Correlation->print_details(fileName);

	delete rb3_Correlation;
}

void test_Shosemaker2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
{
	double eta = 1.036;
	double rhoInfty = 0.0158;

	Correlation* sm2_Correlation = new Shosemaker2_Correlation(fullRank, reducedRank, reductionType, eta, rhoInfty);
	sm2_Correlation->calculate();

	string fileName = "E:\\ShoseMaker2_Correlation.csv";
	sm2_Correlation->print_details(fileName);

	delete sm2_Correlation;
}

void test_Shosemaker3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
{
	double eta1 = 1.036;
	double eta2 = 3.108;
	double rhoInfty = 0.0158;

	Correlation* sm3_Correlation = new Shosemaker3_Correlation(fullRank, reducedRank, reductionType, eta1, eta2, rhoInfty);
	sm3_Correlation->calculate();

	string fileName = "E:\\ShoseMaker3_Correlation.csv";
	sm3_Correlation->print_details(fileName);

	delete sm3_Correlation;
}


void test_XY_beta_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
{
	double beta  = 0.3;
	double alpha = 0.5;

	Correlation* xyBeta_Correlation = new XY_beta_Correlation(fullRank, reducedRank, reductionType, alpha,beta);
	xyBeta_Correlation->calculate();

	string fileName = "E:\\XY_beta_Correlation.csv";
	xyBeta_Correlation->print_details(fileName);

	delete xyBeta_Correlation;
}



void test_PCAEigenVectorRobonato2(size_t fullRank, size_t reducedRank) // to print out eigenVector. // don't care about the reduced rank.
{
	//Robonato2 
	double beta  = 0.1;
	double rhoInfty = 0.0158;

	CorrelationReductionTyype reductionType = CorrelationReductionTyype::PCA;
	Correlation* rb2_Correlation = new Robonato2_Correlation(fullRank, reducedRank, reductionType, beta, rhoInfty);
	rb2_Correlation->calculate();
	Matrix m = rb2_Correlation->get_originalCorrelMatrix();

	SymmetricSchurDecomposition ssd(m);
	Matrix eigenvectors = ssd.eigenvectors();

	string fileName = "E:\\Robonato2_Correlation_PCA_egienVector_Robonato_2.csv";

	ofstream myfile;
	myfile.open(fileName.c_str());

	myfile << "Eigenvectors - in columns" << endl;
	for(size_t i=0; i<eigenvectors.rows(); ++i)
	{
		myfile << i << ",";
		for(size_t j=0; j<eigenvectors.columns(); ++j)
		{
			myfile << eigenvectors[i][j] << ",";
		}
		myfile << std::endl;
	}
	myfile.close();
	delete rb2_Correlation;
}



void test_PCAEigenVectorXY_beta(size_t fullRank, size_t reducedRank) // to print out eigenVector. // don't care about the reduced rank.
{
	//! XY beta
	double beta  = 0.3;
	double alpha = 0.5;



	CorrelationReductionTyype reductionType = CorrelationReductionTyype::PCA;
	Correlation* xyBeta_Correlation = new XY_beta_Correlation(fullRank, reducedRank, reductionType, alpha,beta);
	xyBeta_Correlation->calculate();
	Matrix m = xyBeta_Correlation->get_originalCorrelMatrix();

	SymmetricSchurDecomposition ssd(m);
	Matrix eigenvectors = ssd.eigenvectors();

	string fileName = "E:\\Robonato2_Correlation_PCA_egienVector_xyBeta_Correlation.csv";

	ofstream myfile;
	myfile.open(fileName.c_str());

	myfile << "Eigenvectors - in columns" << endl;
	for(size_t i=0; i<eigenvectors.rows(); ++i)
	{
		myfile << i << ",";
		for(size_t j=0; j<eigenvectors.columns(); ++j)
		{
			myfile << eigenvectors[i][j] << ",";
		}
		myfile << std::endl;
	}
	myfile.close();
	delete xyBeta_Correlation;
}


void testCorrelation()
{
	try
	{
		size_t fullRank = 40;    // 40=15Y/6M
		size_t reducedRank = 3;
		CorrelationReductionTyype reductionType =  CorrelationReductionTyype::RA; // PCA, RA;

		//! TEST Correlation reduction approximation
		//test_Shosemaker2_Correlation(fullRank,reducedRank,reductionType);
		//test_Shosemaker3_Correlation(fullRank,reducedRank,reductionType);
		test_Robonato2_Correlation(fullRank,reducedRank,reductionType);
		//test_Robonato3_Correlation(fullRank,reducedRank,reductionType);
		//test_XY_beta_Correlation(fullRank,reducedRank,reductionType);

		//! Test PCA eigenVector
		//test_PCAEigenVectorRobonato2(fullRank,reducedRank);
		//test_PCAEigenVectorXY_beta(fullRank,reducedRank);

	}catch(string& message)
	{
		cout << "Error message: "  << message << endl;
	}
}






//#pragma once
//
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <math.h>
//
//#include "PCA.h"
//#include "RobonatoAngle.h"
//
//using namespace std;
//using namespace QuantLib;
//
//enum CorrelationReductionTyype {RA, PCA}; // RA: RobonatoAngle
//
//class Correlation
//{
//protected:
//	size_t fullRank_;                 // rank of correlation matrix.
//	size_t reducedRank_;              // rank of the reduced correlation matrix 
//	Matrix originalCorrelMatrix_;  // originalCorrelMatrix, size = (rank_, rank_)
//	Matrix reducedCorrelMatrixB_;  // size = (rank_,reducedRank_)
//	Matrix reducedCorrelMatrixApprox_ ; // approximate the originalCorrelMatrix, size = (rank_, rank_)
//	CorrelationReductionTyype& reductionType_;
//
//public:
//	Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType) // YY: TODO don't like default parameter: use boost::defaultable<size_t> for reduceRank latter.
//		: fullRank_(fullRank),
//		  reducedRank_(reducedRank),
//		  originalCorrelMatrix_(fullRank,fullRank), 
//		  reducedCorrelMatrixB_(fullRank,reducedRank), 
//		  reducedCorrelMatrixApprox_(fullRank,fullRank), 
//		  reductionType_(reductionType)
//	{
//	    //calculateCorrel();       //YY bug fixed: cannot call virtual function here
//		//calculateReducedCorrel();
//	};
//
//	virtual double correl(size_t i, size_t j) = 0;
//
//	void calculate()
//	{
//	    calculateCorrel();              // construct originalCorrelMatrix_
//		calculateReducedCorrelB();	    // from originalCorrelMatrix_ --> reducedCorrelMatrixB_
//		calculateReducedCorrelApprox(); // from reducedCorrelMatrixB_ --> reducedCorrelMatrixApprox_ = B*B^T
//	}
//
//	void calculateCorrel()
//	{
//		for(size_t i=0; i<fullRank_; ++i)
//			for(size_t j=0; j<fullRank_; ++j)
//			    originalCorrelMatrix_[i][j] = correl(i,j);
//	}
//
//	void calculateReducedCorrelB()
//	{
//	    if(reducedRank_ == 0)
//			return;
//
//		switch (reductionType_)
//		{
//			case (CorrelationReductionTyype::PCA):
//				{
//					bool useNormalizeDiagonal = true;
//					reducedCorrelMatrixB_ = PCA::doPCA(originalCorrelMatrix_, reducedRank_, useNormalizeDiagonal, PCARETURNTYPE::MatrixB);  // YY TODO: there is some inefficient copy-coller, to change it latter.			
//					break;
//				}
//			case(CorrelationReductionTyype::RA):
//				{ 
//					//! Do PCA
//					RobonatoAngle rb(originalCorrelMatrix_, reducedRank_);
//					reducedCorrelMatrixB_ =  rb.get_BMatrix();
//					break;
//				}
//			default:
//				throw ("CorrelationReductionTyype not known");
//		}
//	}
//
//	void calculateReducedCorrelApprox()
//	{
//		reducedCorrelMatrixApprox_ = reducedCorrelMatrixB_*transpose(reducedCorrelMatrixB_);
//	}
//
//
//	//! getter.
//	size_t get_fullRank(){return fullRank_;}      
//	size_t get_reducedRank(){return reducedRank_;}
//	Matrix get_originalCorrelMatrix(){return originalCorrelMatrix_;}
//	Matrix get_reducedCorrelMatrixB(){return reducedCorrelMatrixB_;}
//	Matrix get_reducedCorrelMatrixApprox(){return reducedCorrelMatrixApprox_;}
//	CorrelationReductionTyype& get_reductionType(){return reductionType_;}
//
//
//	void print_details(string& fileName)
//	{
//	    ofstream myfile;
//		myfile.open(fileName.c_str());
//
//		myfile << "Matrix" << endl;
//		for(size_t i=0; i<fullRank_; ++i)
//		{
//			for(size_t j=0; j<fullRank_; ++j)
//			{
//			    myfile << originalCorrelMatrix_[i][j] << ",";
//			}
//			myfile << endl;
//		}
//		myfile << endl << endl; 
//
//
//		myfile << "reducedRank MatrixB" << endl;
//		if(reducedRank_ !=0)
//		{
//			for(size_t i=0; i<reducedCorrelMatrixB_.rows(); ++i)
//			{
//				for(size_t j=0; j<reducedCorrelMatrixB_.columns(); ++j)
//				{
//					myfile << reducedCorrelMatrixB_[i][j] << ",";
//				}
//				myfile << endl;
//			}
//		}
//		else
//		{
//		    myfile << "reducedRank = 0, so skip the printing. " << endl; 
//		}
//		myfile << endl << endl; 
//
//
//		myfile << "reducedRank Matrix Approx:" << endl;
//		if(reducedRank_ !=0)
//		{
//			for(size_t i=0; i<reducedCorrelMatrixApprox_.rows(); ++i)
//			{
//				for(size_t j=0; j<reducedCorrelMatrixApprox_.columns(); ++j)
//				{
//					myfile << reducedCorrelMatrixApprox_[i][j] << ",";
//				}
//				myfile << endl;
//			}
//		}
//		else
//		{
//		    myfile << "reducedRank = 0, so skip the printing. " << endl; 
//		}
//		myfile << endl << endl; 
//
//
//		myfile << "difference between original Matrix & reducedRank Matrix" << endl;
//		if(reducedRank_ !=0)
//		{
//			for(size_t i=0; i<fullRank_; ++i)
//			{
//				for(size_t j=0; j<fullRank_; ++j)
//				{
//					myfile << originalCorrelMatrix_[i][j] - reducedCorrelMatrixApprox_[i][j] << ",";
//				}
//				myfile << endl;
//			}
//		}
//		else
//		{
//		    myfile << "reducedRank = 0, so skip the printing. " << endl; 
//		}
//
//		myfile.close();
//	}
//};
//
//class Shosemaker2_Correlation : public Correlation
//{
//private:
//	double eta_;
//	double rhoInfty_;
//
//public:
//	Shosemaker2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType, double eta, double rhoInfty) // // YY: TODO don't like default parameter: use boost::defaultable<size_t> for reduceRank latter.
//		: Correlation(fullRank,reducedRank, reductionType), 
//		  eta_(eta),
//		  rhoInfty_(rhoInfty)
//	{
//	    if(!checkParams())
//			throw("Error in Shosemaker2_Correlation:: Parameters of class Correlation is not permitted.");
//	}
//
//	bool checkParams()
//	{
//	    std::cout << "condition not implemented yet... " << std::endl;
//		return true;
//	}
//
//	double correl(size_t index_i, size_t index_j) 
//	{
//		size_t i = index_i + 1;  // convert i,j \in [0,rank-1] --> [1,rank]
//		size_t j = index_j + 1;
//
//	    double coeff = -abs(i-j)/(double)(fullRank_-1);
//
//		double term1 = -log(rhoInfty_);
//		double term2 = eta_
//			           * (i*i + j*j + i*j - 3*i*fullRank_ - 3*j*fullRank_ +3*i + 3*j +2*fullRank_*fullRank_ - fullRank_ - 4)
//					   / ( (fullRank_-2)*(fullRank_-3) );
//
//		double termSum = term1 + term2;
//		return exp (coeff*termSum);
//	}
//
//
//};
//
////! YY  the formula is not sure correct: result is different from the X-report ??? !!! ---- TOCHECK 
//class Shosemaker3_Correlation : public Correlation
//{
//private:
//	double eta1_;
//	double eta2_;
//	double rhoInfty_;
//
//public:
//	Shosemaker3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType, double eta1, double eta2, double rhoInfty)
//		: Correlation(fullRank,reducedRank, reductionType),
//		  eta1_(eta1), 
//		  eta2_(eta2),
//		  rhoInfty_(rhoInfty)
//	{
//	    if(!checkParams())
//			throw("Error in Shosemaker3_Correlation: Parameters of class Correlation is not permitted.");
//	}
//
//	bool checkParams()
//	{
//	    if(3*eta1_ < eta2_ || eta2_ <0 || 0 > eta1_+ eta2_ || eta1_+ eta2_ > -log(rhoInfty_))
//			return false;
//		else
//			return true;
//	}
//
//	double correl(size_t index_i, size_t index_j) 
//	{
//		size_t i = index_i + 1;  // convert index: i,j \in [0,rank-1] --> [1,rank]
//		size_t j = index_j + 1;
//
//	    double coeff = -abs(i-j)/(double)(fullRank_-1);
//
//
//		double term1 = -log(rhoInfty_);
//		double term2 = eta1_
//			           * (i*i + j*j + i*j - 3*i*fullRank_ - 3*j*fullRank_ +3*i + 3*j +2*fullRank_*fullRank_ - fullRank_ - 4)
//					   / ( (fullRank_-2)*(fullRank_-3) );
//		double term3 = eta2_ 
//			           * (i*i + j*j + i*j - i*fullRank_ - j*fullRank_ -3*i -3*j + 3*fullRank_ + 2)
//					   / ( (fullRank_-2)*(fullRank_-3) );
//
//		double termSum = term1 + term2 + term3;
//		return exp (coeff*termSum);
//	}
//};	
//
//
//class Robonato2_Correlation : public Correlation
//{
//private:
//	double beta_;
//	double rhoInfty_;
//
//public:
//	Robonato2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType, double beta, double rhoInfty)
//		: Correlation(fullRank,reducedRank, reductionType),
//		  beta_(beta),
//		  rhoInfty_(rhoInfty)
//	{
//	    if(!checkParams())
//			throw("Error in Robonato2_Correlation: Parameters of class Correlation is not permitted.");
//	}
//
//	bool checkParams()
//	{
//	    std::cout << "condition not implemented yet... " << std::endl;
//		//! YY: TODO:  not sure if this is the good condition
//		if(beta_ > 0) 
//			return true;
//		else 
//			return false;
//	}
//
//	double correl(size_t index_i, size_t index_j) 
//	{
//		size_t i = index_i + 1;  // convert i,j \in [0,rank-1] --> [1,rank]
//		size_t j = index_j + 1;
//        
//		double exp_index = -beta_*abs(i-j);
//		return rhoInfty_ + (1-rhoInfty_)* exp(exp_index);
//	}
//};	
//
//class Robonato3_Correlation : public Correlation
//{
//private:
//	double alpha_;
//	double beta_;
//	double rhoInfty_;
//
//public:
//	Robonato3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType, double alpha, double beta, double rhoInfty)
//		: Correlation(fullRank, reducedRank, reductionType),
//		  alpha_(alpha), 
//		  beta_(beta),
//		  rhoInfty_(rhoInfty)
//	{
//	    if(!checkParams())
//			throw("Error in Robonato3_Correlation: Parameters of class Correlation is not permitted.");
//	}
//
//	bool checkParams()
//	{
//	    std::cout << "condition not implemented yet... " << std::endl;
//		//! YY: not sure if this is the good condition
//		if(alpha_ < 0 && beta_ - alpha_ > 0) 
//			return true;
//		else 
//			return false;
//	}
//
//	double correl(size_t index_i, size_t index_j) // convert i,j \in [0,rank-1] --> [1,rank]
//	{
//		size_t i = index_i + 1;
//		size_t j = index_j + 1;
//        
//		double exp_index = -abs(i-j)*(beta_-alpha_*(max(i,j)-1));
//		return rhoInfty_ + (1-rhoInfty_)* exp(exp_index);
//	}
//};	
//
//class XY_beta_Correlation : public Correlation
//{
//private:
//	double alpha_;
//	double beta_;
//
//public:
//	XY_beta_Correlation(size_t fullRank, 
//						  size_t reducedRank, 
//						  CorrelationReductionTyype& reductionType, 
//						  double alpha, 
//						  double beta)
//		: Correlation(fullRank, reducedRank, reductionType),
//		  alpha_(alpha), 
//		  beta_(beta)
//	{
//	    if(!checkParams())
//			throw("Error in Robonato3_Correlation: Parameters of class Correlation is not permitted.");
//	}
//
//	bool checkParams()
//	{
//	    std::cout << "condition not implemented yet... " << std::endl;
//		if(beta_<0 || alpha_<0)
//			throw("Error not permitted parameters");
//	}
//
//	double correl(size_t index_i, size_t index_j) // convert i,j \in [0,rank-1] --> [1,rank]
//	{
//		size_t i = index_i + 1;
//		size_t j = index_j + 1;
//        
//		double numerator   = std::abs((double)j-i);
//		double denominator = std::pow((double)i+j, alpha_);
//		double fraction = numerator/denominator; 
//        return exp(-beta_*fraction);
//	}
//};	
//
//
//
////-----------------------------------------------------------------------------------------------
////
////                                             Test 
////
////-----------------------------------------------------------------------------------------------
//void test_Robonato2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
//{
//	double beta  = 0.1;
//	double rhoInfty = 0.0158;
//
//	Correlation* rb2_Correlation = new Robonato2_Correlation(fullRank, reducedRank, reductionType, beta, rhoInfty);
//	rb2_Correlation->calculate();
//
//	string fileName = "E:\\Robonato2_Correlation.csv";
//	rb2_Correlation->print_details(fileName);
//
//	delete rb2_Correlation;
//}
//
//void test_Robonato3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
//{
//	double alpha = -0.001;
//	double beta  = 0.1;
//	double rhoInfty = 0.0158;
//
//	Correlation* rb3_Correlation = new Robonato3_Correlation(fullRank, reducedRank, reductionType, alpha, beta, rhoInfty);
//	rb3_Correlation->calculate();
//
//	string fileName = "E:\\Robonato3_Correlation.csv";
//	rb3_Correlation->print_details(fileName);
//
//	delete rb3_Correlation;
//}
//
//void test_Shosemaker2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
//{
//	double eta = 1.036;
//	double rhoInfty = 0.0158;
//
//	Correlation* sm2_Correlation = new Shosemaker2_Correlation(fullRank, reducedRank, reductionType, eta, rhoInfty);
//	sm2_Correlation->calculate();
//
//	string fileName = "E:\\ShoseMaker2_Correlation.csv";
//	sm2_Correlation->print_details(fileName);
//
//	delete sm2_Correlation;
//}
//
//void test_Shosemaker3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
//{
//	double eta1 = 1.036;
//	double eta2 = 3.108;
//	double rhoInfty = 0.0158;
//
//	Correlation* sm3_Correlation = new Shosemaker3_Correlation(fullRank, reducedRank, reductionType, eta1, eta2, rhoInfty);
//	sm3_Correlation->calculate();
//
//	string fileName = "E:\\ShoseMaker3_Correlation.csv";
//	sm3_Correlation->print_details(fileName);
//
//	delete sm3_Correlation;
//}
//
//
//void test_XY_beta_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype& reductionType)
//{
//	double beta  = 0.3;
//	double alpha = 0.5;
//
//	Correlation* xyBeta_Correlation = new XY_beta_Correlation(fullRank, reducedRank, reductionType, alpha,beta);
//	xyBeta_Correlation->calculate();
//
//	string fileName = "E:\\XY_beta_Correlation.csv";
//	xyBeta_Correlation->print_details(fileName);
//
//	delete xyBeta_Correlation;
//}
//
//
//
//void test_PCAEigenVectorRobonato2(size_t fullRank, size_t reducedRank) // to print out eigenVector. // don't care about the reduced rank.
//{
//	//Robonato2 
//	double beta  = 0.1;
//	double rhoInfty = 0.0158;
//
//	CorrelationReductionTyype reductionType = CorrelationReductionTyype::PCA;
//	Correlation* rb2_Correlation = new Robonato2_Correlation(fullRank, reducedRank, reductionType, beta, rhoInfty);
//	rb2_Correlation->calculate();
//	Matrix m = rb2_Correlation->get_originalCorrelMatrix();
//
//	SymmetricSchurDecomposition ssd(m);
//	Matrix eigenvectors = ssd.eigenvectors();
//
//	string fileName = "E:\\Robonato2_Correlation_PCA_egienVector_Robonato_2.csv";
//
//	ofstream myfile;
//	myfile.open(fileName.c_str());
//
//	myfile << "Eigenvectors - in columns" << endl;
//	for(size_t i=0; i<eigenvectors.rows(); ++i)
//	{
//		myfile << i << ",";
//		for(size_t j=0; j<eigenvectors.columns(); ++j)
//		{
//			myfile << eigenvectors[i][j] << ",";
//		}
//		myfile << std::endl;
//	}
//	myfile.close();
//	delete rb2_Correlation;
//}
//
//
//
//void test_PCAEigenVectorXY_beta(size_t fullRank, size_t reducedRank) // to print out eigenVector. // don't care about the reduced rank.
//{
//	//! XY beta
//	double beta  = 0.3;
//	double alpha = 0.5;
//
//
//
//	CorrelationReductionTyype reductionType = CorrelationReductionTyype::PCA;
//	Correlation* xyBeta_Correlation = new XY_beta_Correlation(fullRank, reducedRank, reductionType, alpha,beta);
//	xyBeta_Correlation->calculate();
//	Matrix m = xyBeta_Correlation->get_originalCorrelMatrix();
//
//	SymmetricSchurDecomposition ssd(m);
//	Matrix eigenvectors = ssd.eigenvectors();
//
//	string fileName = "E:\\Robonato2_Correlation_PCA_egienVector_xyBeta_Correlation.csv";
//
//	ofstream myfile;
//	myfile.open(fileName.c_str());
//
//	myfile << "Eigenvectors - in columns" << endl;
//	for(size_t i=0; i<eigenvectors.rows(); ++i)
//	{
//		myfile << i << ",";
//		for(size_t j=0; j<eigenvectors.columns(); ++j)
//		{
//			myfile << eigenvectors[i][j] << ",";
//		}
//		myfile << std::endl;
//	}
//	myfile.close();
//	delete xyBeta_Correlation;
//}
//
//
//void testCorrelation()
//{
//	try
//	{
//		size_t fullRank = 40;    // 40=15Y/6M
//		size_t reducedRank = 3;
//		CorrelationReductionTyype reductionType =  CorrelationReductionTyype::RA; // PCA, RA;
//
//		//! TEST Correlation reduction approximation
//		//test_Shosemaker2_Correlation(fullRank,reducedRank,reductionType);
//		//test_Shosemaker3_Correlation(fullRank,reducedRank,reductionType);
//		test_Robonato2_Correlation(fullRank,reducedRank,reductionType);
//		//test_Robonato3_Correlation(fullRank,reducedRank,reductionType);
//		//test_XY_beta_Correlation(fullRank,reducedRank,reductionType);
//
//		//! Test PCA eigenVector
//		//test_PCAEigenVectorRobonato2(fullRank,reducedRank);
//		//test_PCAEigenVectorXY_beta(fullRank,reducedRank);
//
//	}catch(string& message)
//	{
//	    cout << "Error message: "  << message << endl;
//	}
//}
