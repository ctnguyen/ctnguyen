#include <cassert>

#include <LMM/generic_path.h>
#include <LMM/helper/Printer.h>
#include <LMM/ModelMCLMM/HGVolatilityFunction.h>




//! Inner class: h vol
//! Attention: a very slow function.
//! indexLibor = i, indexTime = j
//! libor i, in time [T_{j-1}, T_j]
double HGVolatilityFunction::AbcdPWConstFunction::operator()(size_t indexLibor, size_t indexTime) const// operator(i,j) --return vol--> hij, i>=j
{
	//! check index relation
	if(indexLibor<indexTime)
		throw("Error, index relation error!");

	if(indexLibor<1 || indexLibor>lmmTenorStructure_->get_horizon())  // size1 = horizon
		throw("Error, invalid indexLibor!");

	if(indexTime <1)  // size1 = horizon
		throw("Error, invalid indexTime!");

	//! 
	//const double&  t_begin = lmmTenorStructure_->get_tenorDate(indexTime-1); 
	//const double&  t_end   = lmmTenorStructure_->get_tenorDate(indexTime); 
	//double t       = (t_begin + t_end)/2.0; 
	const double&  t       = lmmTenorStructure_->get_tenorDate(indexTime); 

	const double&  T_i     = lmmTenorStructure_->get_tenorDate(indexLibor);        
	double tau     = T_i-t; 

	return abcdFunction_(tau);
}




// ----------------------------------------------------------------------------------------------------------------
//
//                                           hgVolatilityFunction
//
// ----------------------------------------------------------------------------------------------------------------
//! Constructor
HGVolatilityFunction::HGVolatilityFunction(const      AbcdParams& abcdParams,              // h FunctionParam
	                                       ConstLMMTenorStructure lmmTenorStructure)       // horizon = N, total number of libor: L_k, k = [0,N]
	: VolatilityFunction(lmmTenorStructure)
	, horizon_(lmmTenorStructure_->get_horizon())
	, abcdPWConstFunction_(abcdParams, lmmTenorStructure)
	 // YY: A good thing from Adrien, add artificial first row and column (not used!), to make the manipulation of index easier.
	 // piecewise constant vol for: L_k, K = [1,N]
	 , hPWConstFunc_(lmmTenorStructure->get_horizon()+1,lmmTenorStructure->get_horizon()+1)   
	 , gPWConstFunc_(lmmTenorStructure->get_horizon()+1,lmmTenorStructure->get_horizon()+1)
	 //volCumulated_(lmmTenorStructure.get_horizon()+1,lmmTenorStructure.get_horizon()+1, -9.9e10), 
	 //ifVolisUpToDate_(false)
{
	construct_hPWConstFunc();
	construct_gPWConstFunc();
	//precalculateVolCumulated();
	//ifVolisUpToDate_ = true; //! YY whenever reset h or g function, need to set this param to false, to enforce the recalculation of VolCumulated, 
	//                         //     or other pre-calculated item.
}


void HGVolatilityFunction::construct_hPWConstFunc()
{
	//! forget first row/column
	for(size_t indexLibor=1; indexLibor<hPWConstFunc_.size1(); ++indexLibor)
	{
		for(size_t indexTime=1; indexTime<=indexLibor; ++indexTime)  // triangular matrix
		{
			hPWConstFunc_(indexLibor,indexTime) = abcdPWConstFunction_(indexLibor,indexTime);   
		}
	}
}


void HGVolatilityFunction::construct_gPWConstFunc()
{	
	//! forget first row/column
	for(size_t indexLibor=1; indexLibor<hPWConstFunc_.size1(); ++indexLibor)
	{
		for(size_t indexTime=1; indexTime<=indexLibor; ++indexTime)  // triangular matrix
		{
			gPWConstFunc_(indexLibor,indexTime) = 1.0; //YY TODO: to do the change latter.
		}
	}
}

//void hgVolatilityFunction::precalculateVolCumulated()
//{
//	for(size_t indexLibor=1; indexLibor<hPWConstFunc_.size1(); ++indexLibor)
//	{
//		for(size_t indexTime=1; indexTime<=indexLibor; ++indexTime) 
//		{
//			double vol_PWConstIntanteneous     = hPWConstFunc_(indexLibor, indexTime)*gPWConstFunc_(indexLibor, indexTime);
//			double vol_integralCurrentInterval = vol_PWConstIntanteneous * lmmTenorStructure_->get_deltaT(indexTime); //! L_{i+1}'s integral vol in [T_j,T_{j+1}] 
//			if(indexTime==1)
//				volCumulated_(indexLibor,indexTime) = vol_integralCurrentInterval;
//			else
//			    volCumulated_(indexLibor,indexTime) = volCumulated_(indexLibor,indexTime-1) + vol_integralCurrentInterval;
//		}
//	}
//}


//! vol
//! i = indexLibor
//! j = indexTime
//! volatility of L_i at [T_{j-1},T_j]
double HGVolatilityFunction::operator()(size_t indexLibor, size_t indexTime) const// operator(i,j) --return vol--> hij, i>=j
{
	//if(ifVolisUpToDate_ = false)  // YY: This is needed for calibration! 
	//	throw("Error Vol need to update before the calculation.");

	if(indexLibor<indexTime)
		throw("Error, index relation error!");

	if(indexLibor<1 || indexLibor>hPWConstFunc_.size1())  // size1 = horizon
		throw("Error, invalid indexLibor!");

	if(indexTime <1)  // size1 = horizon
		throw("Error, invalid indexTime!");

	return hPWConstFunc_(indexLibor, indexTime)*gPWConstFunc_(indexLibor, indexTime);
}


//! Whne t in [T_i,T_{i+1}], return index= i+1
size_t HGVolatilityFunction::indexSearch(const double& t) const
{
	size_t indexsearch;
	 if(t<lmmTenorStructure_->get_tenorDate(0) || t>lmmTenorStructure_->get_tenorDate(horizon_))  // check condition: t in [T_0,T_N]
		for(size_t i=0; i<horizon_; ++i)
		{
			const double&  t1 = lmmTenorStructure_->get_tenorDate(i);
			const double&  t2 = lmmTenorStructure_->get_tenorDate(i+1);
			if(t>=t1 && t<t2)
			{
				indexsearch = i+1;break;
			}
		}
	 return indexsearch;
}


double HGVolatilityFunction::covIntegral( size_t indexTime_i,
										  size_t indexTime_j,
										  size_t indexLibor_i,
										  size_t indexLibor_j) const
{
	assert(indexLibor_i <= indexLibor_j);

	size_t indexLiborMin   = indexLibor_i;
	size_t indexTime_begin = std::min(indexTime_i,indexLiborMin);
	size_t indexTime_end   = std::min(indexTime_j,indexLiborMin);

	double covIntegralValue = 0.0;
	for(size_t indexTime=indexTime_begin; indexTime<indexTime_end; ++indexTime)
	{
		const double& deltaT = lmmTenorStructure_->get_deltaT(indexTime);
		covIntegralValue += this->operator()(indexLibor_i,indexTime+1) * this->operator()(indexLibor_j,indexTime+1) * deltaT;
	}	
	return covIntegralValue;
}

void HGVolatilityFunction::print(const std::string& filename) const  // OK: test passed.
{
	//std::string fileName = "HGVolatilityFunction.csv";
	std::string path = LMM::get_output_path() + filename;
	
	std::vector<PrintElement_PTR> elements_print;

	//! Abcd function for h
	std::vector<double> abcdVect; //push the abcdParams into a std::vector
	abcdVect.push_back(abcdPWConstFunction_.get_AbcdFunction().a() );
	abcdVect.push_back(abcdPWConstFunction_.get_AbcdFunction().b() );
	abcdVect.push_back(abcdPWConstFunction_.get_AbcdFunction().c() );
	abcdVect.push_back(abcdPWConstFunction_.get_AbcdFunction().d() );

	PrintElement_PTR abcdParamVector     = PrintElement_PTR(new VectorPrintElement<std::vector<double> >("abcdParamVector",  abcdVect ) );
	PrintElement_PTR abcdFunctionFormula = PrintElement_PTR(new ScalarPrintElement<std::string>("abcdFunctionFormula",  "abcdFunc(tau) = (a+ b*tau)*exp(-c*tau) + d   tau = T_i-t") );
	elements_print.push_back(abcdParamVector);
	elements_print.push_back(abcdFunctionFormula);

	//! h,g,hgMatrix
	typedef boost::numeric::ublas::matrix<double> matrix;
	matrix hMatrix(horizon_+1, horizon_+1);
	matrix gMatrix(horizon_+1, horizon_+1);
	matrix hgMatrix(horizon_+1, horizon_+1);

	for(size_t indexLibor = 1; indexLibor<=horizon_; ++indexLibor)
	{
		for(size_t indexT = 1; indexT<=indexLibor; ++indexT)
		{
			hMatrix(indexLibor,indexT)  = hPWConstFunc_(indexLibor,indexT);
			gMatrix(indexLibor,indexT)  = gPWConstFunc_(indexLibor,indexT);
			hgMatrix(indexLibor,indexT) = this->operator()(indexLibor,indexT);
		}
	}

	//seems a problem of shared ptr polymorphisms ... 
	//PrintElement_PTR tenorType_print    = PrintElement_PTR(new ScalarPrintElement<std::string>("tenorType", tenorType_));
	//PrintElement_PTR horizon_print      = PrintElement_PTR(new ScalarPrintElement<Name::indexInLMMTenorStructure>("horizon", horizon_));
	PrintElement_PTR hMatrix_print   = PrintElement_PTR(new MatrixPrintElement<matrix>("hMatrix",  hMatrix));
	PrintElement_PTR gMatrix_print   = PrintElement_PTR(new MatrixPrintElement<matrix>("gMatrix",  gMatrix));
	PrintElement_PTR hgMatrix_print  = PrintElement_PTR(new MatrixPrintElement<matrix>("hgMatrix", hgMatrix));


	//elements_print.push_back(tenorType_print);
	elements_print.push_back(hMatrix_print);
	elements_print.push_back(gMatrix_print);
	elements_print.push_back(hgMatrix_print);

	Printer printer(path, elements_print);
	printer.print();
}