#include <LMM/ModelMCLMM/Lmm.h>
#include <cassert>


//----------  TENSOR  --------------

Tensor::Tensor(size_t size1, size_t size2, size_t size3) : tensor_(size1, matrix(size2, size3)){}

double & Tensor::operator()(size_t index_T, size_t indexLibor_i, size_t indexLibor_j) 
{
	//! YY Attention: This is a special condition for My LMM implementation, not general tensor condition.
	//! YY TODO: remove this check when the code is stable.
	assert(index_T >=1 && indexLibor_i>=index_T && indexLibor_j >= index_T);
	return tensor_[index_T](indexLibor_i, indexLibor_j);
}

const double & Tensor::operator()(size_t index_T, size_t indexLibor_i, size_t indexLibor_j) const
{
	//! YY Attention: This is a special condition for My LMM implementation, not general tensor condition.
	//! YY TODO: remove this check when the code is stable.
	assert(index_T >=1 && indexLibor_i>=index_T && indexLibor_j >= index_T);
	return tensor_[index_T](indexLibor_i, indexLibor_j);
}


const std::vector<matrix>& Tensor::get_tensor() const { return tensor_; }

void Tensor::set_tensor(std::vector<matrix> val) { tensor_ = val;}

const matrix& Tensor::operator[](size_t indexT) const
{ 
	assert(indexT >=1);
	return tensor_[indexT];
}

void Tensor::write_to_stream(std::ostream& outputstream)const
{
	const unsigned int nbMatrix = tensor_.size();
	for(unsigned int iM=0;iM<nbMatrix;++iM)
	{
		const unsigned int nbLine = tensor_[iM].size1();
		const unsigned int nbCol  = tensor_[iM].size2();
		outputstream <<"Tensor("<<iM<<"): [";
		for(unsigned int i=0;i<nbLine;++i)
		{
			outputstream<<tensor_[iM](i,0) ;
			for(unsigned int j=1;j<nbCol;++j)
			{
				outputstream<<";"<<tensor_[iM](i,j);
			}
			outputstream<<"] [";		
		}	
		outputstream<<std::endl;
	}
}

std::ostream& operator<<(std::ostream& os, const Tensor& m_tensor)
{
	m_tensor.write_to_stream(os); return os;
}
//----------  TENSOR  --------------





Lmm::Lmm(const Dispersion&                  dispersion,
		 const std::vector<double>&         shifts,           // size = N+1
		 const std::vector<double>&         liborsInitValue)
		 : dispersion_(dispersion)
		 , shifts_(shifts)
		 , covarianceTensor_         (dispersion_.get_horizon()+1, dispersion_.get_horizon()+1,dispersion_.get_horizon()+1)
		 , cumulatedCovarianceTensor_(dispersion_.get_horizon()+1, dispersion_.get_horizon()+1,dispersion_.get_horizon()+1)
		 , liborsInitValue_(liborsInitValue)
{
	initCovarianceTensor();
	initCumulatedCovarianceTensor();
}




void Lmm::initCovarianceTensor()
{
	//! YY TODO: make the not initialized value to #IND

	// tensor_:  k,i,j
	// L_i, L_j 's integral of vol in [T_{k-1},T_k]: i,j >= k
	size_t horizon = dispersion_.get_horizon();
	for(size_t indexTime = 1; indexTime <= horizon; ++indexTime)
	{
		for(size_t indexLibor_i = indexTime; indexLibor_i <= horizon; ++indexLibor_i)
		{
			for(size_t indexLibor_j = indexLibor_i; indexLibor_j <= horizon; ++indexLibor_j)
			{
				covarianceTensor_(indexTime, indexLibor_i, indexLibor_j) = dispersion_.covIntegral(indexTime-1,
					indexTime,
					indexLibor_i,
					indexLibor_j);

				//! because of the symmetric of the tensor
				covarianceTensor_(indexTime, indexLibor_i, indexLibor_j) = covarianceTensor_(indexTime, indexLibor_i, indexLibor_j);

			}
		}
	}
}

void Lmm::initCumulatedCovarianceTensor()
{
	// tensor_:  k,i,j
	// L_i, L_j 's integral of vol in [T_0,T_k]: i,j >= k
	size_t horizon = dispersion_.get_horizon();
	for(size_t indexTime = 1; indexTime <= horizon; ++indexTime)
	{
		for(size_t indexLibor_i = indexTime; indexLibor_i <= horizon; ++indexLibor_i)
		{
			for(size_t indexLibor_j = indexLibor_i; indexLibor_j <= horizon; ++indexLibor_j)
			{
				if(indexTime ==1)
				{
					cumulatedCovarianceTensor_(indexTime, indexLibor_i, indexLibor_j) = covarianceTensor_(indexTime, indexLibor_i, indexLibor_j);
				}
				else
				{
					cumulatedCovarianceTensor_(indexTime, indexLibor_i, indexLibor_j) =  cumulatedCovarianceTensor_(indexTime-1, indexLibor_i, indexLibor_j) + covarianceTensor_(indexTime, indexLibor_i, indexLibor_j);
				}
			}
		}
	}

}


size_t Lmm::get_horizon() const {return dispersion_.get_horizon();}

ConstLMMTenorStructure Lmm::get_LMMTenorStructure () const {return dispersion_.get_lmmTenorStructure();}

const std::vector<double>& Lmm::get_shifts()			  const {return shifts_;}

const std::vector<double>& Lmm::get_liborsInitValue()  const {return liborsInitValue_;}


const double& Lmm::get_covarianceTensor(size_t indexTime, size_t indexLibor_i, size_t indexLibor_j) const
{
	assert(indexTime <= indexLibor_i && indexTime <= indexLibor_j);
	return covarianceTensor_(indexTime, indexLibor_i, indexLibor_j);
}

const double& Lmm::get_cumulatedcovarianceTensor(size_t indexTime, size_t indexLibor_i, size_t indexLibor_j) const
{
	assert(indexTime <= indexLibor_i && indexTime <= indexLibor_j);
	return cumulatedCovarianceTensor_(indexTime, indexLibor_i, indexLibor_j);
}


void Lmm::write_to_stream(std::ostream& outputstream)const
{
	outputstream<<"cumulatedCovarianceTensor_"<<std::endl;
	cumulatedCovarianceTensor_.write_to_stream(outputstream);

}

std::ostream& operator<<(std::ostream& os, const Lmm& lmm)
{
	lmm.write_to_stream(os); return os;
}