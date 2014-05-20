#include <boost/numeric/ublas/matrix.hpp>

#include <LMM/helper/Printer.h>
#include <LMM/helper/TypeConverter.h>
#include <LMM/ModelMCLMM/Correlation.h>

// ------------------------------------------------------------------------------
//
//                          Correlation
//
// ------------------------------------------------------------------------------

Correlation::Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType) // YY: TODO don't like default parameter: use boost::defaultable<size_t> for reduceRank latter.
	: fullRank_(fullRank),
	reducedRank_(reducedRank),
	originalCorrelMatrix_(fullRank,fullRank), 
	reducedCorrelMatrixB_(fullRank,reducedRank), 
	reducedCorrelMatrixApprox_(fullRank,fullRank), 
	reductionType_(reductionType),
	flagApproxConstruced_(false)
{
	//calculateCorrel();       //YY bug fixed: cannot call virtual function here
	//calculateReducedCorrel();
	assert(fullRank_>0 && reducedRank_>0 && reducedRank_<fullRank_);
}


void Correlation::calculate()
{
	calculateCorrelOriginal();              // construct originalCorrelMatrix_
	calculateReducedCorrelB();	    // from originalCorrelMatrix_ --> reducedCorrelMatrixB_
	calculateReducedCorrelApprox(); // from reducedCorrelMatrixB_ --> reducedCorrelMatrixApprox_ = B*B^T
	flagApproxConstruced_ = true;
}

void Correlation::calculateCorrelOriginal()
{
	for(size_t i=0; i<fullRank_; ++i)
		for(size_t j=0; j<fullRank_; ++j)
			originalCorrelMatrix_[i][j] = correlOriginal(i,j);
}

void Correlation::calculateReducedCorrelB()
{	
	switch (reductionType_)
	{
	case (CorrelationReductionTyype::PCA):
		{
			bool useNormalizeDiagonal = true;
			reducedCorrelMatrixB_ = PCA::doPCA(originalCorrelMatrix_, reducedRank_, useNormalizeDiagonal);  // YY TODO: there is some inefficient copy-coller, to change it latter.			
			break;
		}
	case(CorrelationReductionTyype::RA):
		{ 
			//! Do PCA
			RobonatoAngle rb(originalCorrelMatrix_, reducedRank_);
			reducedCorrelMatrixB_ =  rb.get_BMatrix();
			break;
		}
	default:
		throw ("CorrelationReductionTyype not known");
	}
}

void Correlation::calculateReducedCorrelApprox()
{
	reducedCorrelMatrixApprox_ = reducedCorrelMatrixB_*transpose(reducedCorrelMatrixB_);
}


//! getter.
size_t Correlation::get_fullRank(){return fullRank_;}      
size_t Correlation::get_reducedRank(){return reducedRank_;}
const Matrix& Correlation::get_originalCorrelMatrix() const {return originalCorrelMatrix_;}
const Matrix& Correlation::get_reducedCorrelMatrixB() const {return reducedCorrelMatrixB_;}
const Matrix& Correlation::get_reducedCorrelMatrixApprox() const {return reducedCorrelMatrixApprox_;}
const CorrelationReductionTyype::CorrelationReductionTyype& Correlation::get_reductionType() const {return reductionType_;}
const std::string Correlation::get_reductionTypeString() const
{
	if(reductionType_ == CorrelationReductionTyype::PCA)
		return "PCA";
    
	if(reductionType_ == CorrelationReductionTyype::RA)
		return "RA";

	throw("CorrelationReductionTyype is not valid");
}
bool  Correlation::get_flagApproxConstruced()const {return flagApproxConstruced_;}
double Correlation::correlApprox(size_t i, size_t j) const 
{
	assert(flagApproxConstruced_==true);
	return reducedCorrelMatrixApprox_[i][j];
}


void Correlation::print() const
{
	assert(flagApproxConstruced_ == true);

	std::string fileName = "Correlation.csv";
	std::string path = printPathOutput + fileName;

	std::vector<PrintElement_PTR> elements_print;

	//! CorrelationMatrix
	PrintElement_PTR to_print;

	to_print = PrintElement_PTR(new ScalarPrintElement<size_t>("fullRank",fullRank_));
	elements_print.push_back(to_print);

	to_print  = PrintElement_PTR(new ScalarPrintElement<size_t>("reducedRank",reducedRank_));
	elements_print.push_back(to_print);

	to_print  = PrintElement_PTR(new ScalarPrintElement<std::string>("reductionType_",get_reductionTypeString()));
	elements_print.push_back(to_print);

	typedef boost::numeric::ublas::matrix<double> matrix;

	to_print      = PrintElement_PTR(new MatrixPrintElement<matrix>("originalCorrelMatrix_", QLMatrix2BoostMatrix(originalCorrelMatrix_)));
	elements_print.push_back(to_print);

	to_print      = PrintElement_PTR(new MatrixPrintElement<matrix>("reducedCorrelMatrixB_", QLMatrix2BoostMatrix(reducedCorrelMatrixB_)));
	elements_print.push_back(to_print);

	to_print      = PrintElement_PTR(new MatrixPrintElement<matrix>("reducedCorrelMatrixApprox_", QLMatrix2BoostMatrix(reducedCorrelMatrixApprox_)));
	elements_print.push_back(to_print);

	
	Printer printer(path, elements_print);
	printer.print();
}

void Correlation::print_details(string& fileName) const
{
	ofstream myfile;
	myfile.open(fileName.c_str());

	myfile << "Matrix" << endl;
	for(size_t i=0; i<fullRank_; ++i)
	{
		for(size_t j=0; j<fullRank_; ++j)
		{
			myfile << originalCorrelMatrix_[i][j] << ",";
		}
		myfile << endl;
	}
	myfile << endl << endl; 


	myfile << "reducedRank MatrixB" << endl;
	if(reducedRank_ !=0)
	{
		for(size_t i=0; i<reducedCorrelMatrixB_.rows(); ++i)
		{
			for(size_t j=0; j<reducedCorrelMatrixB_.columns(); ++j)
			{
				myfile << reducedCorrelMatrixB_[i][j] << ",";
			}
			myfile << endl;
		}
	}
	else
	{
		myfile << "reducedRank = 0, so skip the printing. " << endl; 
	}
	myfile << endl << endl; 


	myfile << "reducedRank Matrix Approx:" << endl;
	if(reducedRank_ !=0)
	{
		for(size_t i=0; i<reducedCorrelMatrixApprox_.rows(); ++i)
		{
			for(size_t j=0; j<reducedCorrelMatrixApprox_.columns(); ++j)
			{
				myfile << reducedCorrelMatrixApprox_[i][j] << ",";
			}
			myfile << endl;
		}
	}
	else
	{
		myfile << "reducedRank = 0, so skip the printing. " << endl; 
	}
	myfile << endl << endl; 


	myfile << "difference between original Matrix & reducedRank Matrix" << endl;
	if(reducedRank_ !=0)
	{
		for(size_t i=0; i<fullRank_; ++i)
		{
			for(size_t j=0; j<fullRank_; ++j)
			{
				myfile << originalCorrelMatrix_[i][j] - reducedCorrelMatrixApprox_[i][j] << ",";
			}
			myfile << endl;
		}
	}
	else
	{
		myfile << "reducedRank = 0, so skip the printing. " << endl; 
	}

	myfile.close();
}



// ------------------------------------------------------------------------------
//
//                          Shosemaker2_Correlation
//
// ------------------------------------------------------------------------------

Shosemaker2_Correlation::Shosemaker2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType, double eta, double rhoInfty) // // YY: TODO don't like default parameter: use boost::defaultable<size_t> for reduceRank latter.
	: Correlation(fullRank,reducedRank, reductionType), 
	eta_(eta),
	rhoInfty_(rhoInfty)
{
	if(!checkParams())
		throw("Error in Shosemaker2_Correlation:: Parameters of class Correlation is not permitted.");
}

bool Shosemaker2_Correlation::checkParams() const
{
	std::cout << "condition not implemented yet... " << std::endl;
	return true;
}

double Shosemaker2_Correlation::correlOriginal(size_t index_i, size_t index_j) const
{
	size_t i = index_i + 1;  // convert i,j \in [0,rank-1] --> [1,rank]
	size_t j = index_j + 1;

	double coeff = -abs((int)i-(int)j)/(double)(fullRank_-1);

	double term1 = -log(rhoInfty_);
	double term2 = eta_
		* (i*i + j*j + i*j - 3*i*fullRank_ - 3*j*fullRank_ +3*i + 3*j +2*fullRank_*fullRank_ - fullRank_ - 4)
		/ ( (fullRank_-2)*(fullRank_-3) );

	double termSum = term1 + term2;
	return exp (coeff*termSum);
}



// ------------------------------------------------------------------------------
//
//                          Shosemaker3_Correlation
//
// ------------------------------------------------------------------------------
Shosemaker3_Correlation::Shosemaker3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType, double eta1, double eta2, double rhoInfty)
	: Correlation(fullRank,reducedRank, reductionType),
	eta1_(eta1), 
	eta2_(eta2),
	rhoInfty_(rhoInfty)
{
	if(!checkParams())
		throw("Error in Shosemaker3_Correlation: Parameters of class Correlation is not permitted.");
}

bool Shosemaker3_Correlation::checkParams() const
{
	if(3*eta1_ < eta2_ || eta2_ <0 || 0 > eta1_+ eta2_ || eta1_+ eta2_ > -log(rhoInfty_))
		return false;
	else
		return true;
}

double Shosemaker3_Correlation::correlOriginal(size_t index_i, size_t index_j) const
{
	size_t i = index_i + 1;  // convert index: i,j \in [0,rank-1] --> [1,rank]
	size_t j = index_j + 1;

	double coeff = -abs((int)i-(int)j)/(double)(fullRank_-1);


	double term1 = -log(rhoInfty_);
	double term2 = eta1_
		* (i*i + j*j + i*j - 3*i*fullRank_ - 3*j*fullRank_ +3*i + 3*j +2*fullRank_*fullRank_ - fullRank_ - 4)
		/ ( (fullRank_-2)*(fullRank_-3) );
	double term3 = eta2_ 
		* (i*i + j*j + i*j - i*fullRank_ - j*fullRank_ -3*i -3*j + 3*fullRank_ + 2)
		/ ( (fullRank_-2)*(fullRank_-3) );

	double termSum = term1 + term2 + term3;
	return exp (coeff*termSum);
}



// ------------------------------------------------------------------------------
//
//                          Robonato2_Correlation
//
// ------------------------------------------------------------------------------
Robonato2_Correlation::Robonato2_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType, double beta, double rhoInfty)
	: Correlation(fullRank,reducedRank, reductionType),
	beta_(beta),
	rhoInfty_(rhoInfty)
{
	if(!checkParams())
		throw("Error in Robonato2_Correlation: Parameters of class Correlation is not permitted.");
}

bool Robonato2_Correlation::checkParams() const
{
	std::cout << "condition not implemented yet... " << std::endl;
	//! YY: TODO:  not sure if this is the good condition
	if(beta_ > 0) 
		return true;
	else 
		return false;
}

double Robonato2_Correlation::correlOriginal(size_t index_i, size_t index_j) const
{
	size_t i = index_i + 1;  // convert i,j \in [0,rank-1] --> [1,rank]
	size_t j = index_j + 1;

	double exp_index = -beta_*abs((int)i-(int)j);
	return rhoInfty_ + (1-rhoInfty_)* exp(exp_index);
}


// ------------------------------------------------------------------------------
//
//                          Robonato3_Correlation
//
// ------------------------------------------------------------------------------

Robonato3_Correlation::Robonato3_Correlation(size_t fullRank, size_t reducedRank, CorrelationReductionTyype::CorrelationReductionTyype& reductionType, double alpha, double beta, double rhoInfty)
	: Correlation(fullRank, reducedRank, reductionType),
	alpha_(alpha), 
	beta_(beta),
	rhoInfty_(rhoInfty)
{
	if(!checkParams())
		throw("Error in Robonato3_Correlation: Parameters of class Correlation is not permitted.");
}

bool Robonato3_Correlation::checkParams() const
{
	std::cout << "condition not implemented yet... " << std::endl;
	//! YY: not sure if this is the good condition
	if(alpha_ < 0 && beta_ - alpha_ > 0) 
		return true;
	else 
		return false;
}

double Robonato3_Correlation::correlOriginal(size_t index_i, size_t index_j) const// convert i,j \in [0,rank-1] --> [1,rank]
{
	size_t i = index_i + 1;
	size_t j = index_j + 1;

	double exp_index = -abs((int)i-(int)j)*(beta_-alpha_*(max(i,j)-1));
	return rhoInfty_ + (1-rhoInfty_)* exp(exp_index);
}



// ------------------------------------------------------------------------------
//
//                          XY_beta_Correlation
//
// ------------------------------------------------------------------------------

XY_beta_Correlation::XY_beta_Correlation(size_t fullRank, 
	size_t reducedRank, 
	CorrelationReductionTyype::CorrelationReductionTyype& reductionType,
	double alpha, 
	double beta)
	: Correlation(fullRank, reducedRank, reductionType),
	alpha_(alpha), 
	beta_(beta)
{
	if(!checkParams())
		throw("Error in Robonato3_Correlation: Parameters of class Correlation is not permitted.");
}

bool XY_beta_Correlation::checkParams() const
{
	std::cout << "condition not implemented yet... " << std::endl;
	if(beta_<0 || alpha_<0)
		throw("Error not permitted parameters");
	return true;
}

double XY_beta_Correlation::correlOriginal(size_t index_i, size_t index_j) const// convert i,j \in [0,rank-1] --> [1,rank]
{
	size_t i = index_i + 1;
	size_t j = index_j + 1;

	double numerator   = std::abs((double)j-i);
	double denominator = std::pow((double)i+j, alpha_);
	double fraction = numerator/denominator; 
	return exp(-beta_*fraction);
}


// ------------------------------------------------------------------------------
//
//                          Const_Correlation
//
// ------------------------------------------------------------------------------

Const_Correlation::Const_Correlation  (size_t fullRank, 
	size_t reducedRank, 
	CorrelationReductionTyype::CorrelationReductionTyype& reductionType,
	double correlConst)
	:Correlation(fullRank,reducedRank,reductionType),
		correlConst_(correlConst)
{}

bool Const_Correlation::checkParams() const
{
	if(correlConst_ <= 1.0 && correlConst_ >= -1.0)
		return true;
	else 
		return false;
}

double Const_Correlation::correlOriginal(size_t index_i, size_t index_j) const// convert i,j \in [0,rank-1] --> [1,rank]
{
	if(index_i != index_j)
		return correlConst_;
	else
		return 1.0;
}
	
