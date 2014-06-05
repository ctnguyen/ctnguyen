#include <cassert>
#include <vector>

//#include <boost/math/distributions.hpp>
//#include <boost\bind.hpp>
//#include <ql\math\distributions\normaldistribution.hpp>

#include <LMM/pricer/LmmApproxVanillaSwaptionPricer.h>

LmmApproxVanillaSwaptionPricer::LmmApproxVanillaSwaptionPricer(const Lmm_PTR& lmmModel, const VanillaSwaption_PTR& swaption)
	: VanillaSwapPricer(lmmModel->get_LMMTenorStructure() )
	, lmm_(lmmModel)
	, vanillaswaption_(swaption)
	, ZC_(lmm_->get_horizon()+2)
	, numeraire_(lmm_->get_horizon()+2)
	, omega0_(vanillaswaption_->getUnderlyingSwap().get_floatingLegPaymentIndexSchedule().size() )
{
	assert(lmm_->get_LMMTenorStructure()->get_tenorDate()[0] == 0.0);

	this->preCalculateNumeraireAndZC();
	this->preCalculateOmega();
}

LmmApproxVanillaSwaptionPricer::~LmmApproxVanillaSwaptionPricer()
{

}


void LmmApproxVanillaSwaptionPricer::preCalculateNumeraireAndZC()
{
	const std::vector<double>& deltaT = lmm_->get_LMMTenorStructure()->get_deltaT();
	const std::vector<double>& liborsInitValue = lmm_->get_liborsInitValue();
	ZC_[0] = 1.0;numeraire_[0]=1.0;
	for(size_t i=1; i<ZC_.size(); ++i)
	{
		size_t indexLibor = i-1;
		ZC_[i] = ZC_[i-1]/(1+deltaT[indexLibor]*liborsInitValue[indexLibor]);
		numeraire_[i] = 1/ZC_[i];
	}
}


void LmmApproxVanillaSwaptionPricer::preCalculateOmega()
{
	LMM::Index indexValuationDate = 0; // computed omega vector valuated at time t=0

	const LMM::VanillaSwap& vanillaSwap = vanillaswaption_->getUnderlyingSwap();
	const double annuityValue = annuity(indexValuationDate, vanillaSwap, numeraire_);

	const std::vector<LMM::Index>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();

	for(size_t itr=0; itr<floatingLegPaymentIndexSchedule.size(); ++itr)
	{
		//! At time T_{i+1}, pay: delta_t*L_i(T_i)
		size_t floatingLegPaymentIndex = floatingLegPaymentIndexSchedule[itr]; // = i+1
		//size_t indexLibor = floatingLegPaymentIndex-1; // =i, because : floatingTenor = lmmTenor  
		//size_t indexT     = indexLibor;                                        // = i
		const std::vector<double>& deltaTFloatingLeg_ = vanillaSwap.get_DeltaTFloatLeg();
		const double& delta_T    = deltaTFloatingLeg_[itr];  
		omega0_[itr] = delta_T*ZC_[floatingLegPaymentIndex] / annuityValue;
	}
}


double LmmApproxVanillaSwaptionPricer::volBlack() const
{
	const LMM::VanillaSwap& vanillaSwap = vanillaswaption_->getUnderlyingSwap();

	assert(lmm_->get_horizon() >= vanillaSwap.get_indexEnd()); //! if not cannot price it.
	assert(lmm_->get_LMMTenorStructure()->get_tenorType() == vanillaSwap.get_simulationTenorType() );

	//! Robonato Formula: YY TODO: can be simplified: use the symmetric ! 
	LMM::Index swaptionIndexMaturity = vanillaswaption_->get_indexMaturity();
	const std::vector<double>& liborsInitValue = lmm_->get_liborsInitValue();
	const std::vector<LMM::Index>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();

	double volSquare = 0.0;
	for(size_t i=0; i<floatingLegPaymentIndexSchedule.size(); ++i)
	{
		size_t floatingLegPaymentIndex_i = floatingLegPaymentIndexSchedule[i]; // = i+1
		size_t indexLibor_i = floatingLegPaymentIndex_i - 1;
		//size_t indexT_i = indexLibor_i;
		for(size_t j=0; j<floatingLegPaymentIndexSchedule.size(); ++j)
		{
			size_t floatingLegPaymentIndex_j = floatingLegPaymentIndexSchedule[j]; // = j+1
			size_t indexLibor_j = floatingLegPaymentIndex_j - 1;
			//size_t indexT_j     = indexLibor_j;

			// tensor_(k,i,j): L_i, L_j 's integral of vol in [T_{k-1},T_k]

			const double& cumulated_covariance_tensor = lmm_->get_cumulatedcovarianceTensor(swaptionIndexMaturity, indexLibor_i, indexLibor_j);
			volSquare += omega0_[i]*omega0_[j]*liborsInitValue[indexLibor_i]*liborsInitValue[indexLibor_j]*cumulated_covariance_tensor;
		}
	}

	double swapRate = swapRate_Analytical(vanillaSwap, liborsInitValue); // swapRate at time 0
	double volBlack = std::sqrt(volSquare) * swapRate;

	return volBlack;
}


void LmmApproxVanillaSwaptionPricer::accumulateShiftedSwapRateAndStrike(
	double& out_shifted_swapRate_T0 ,
	double& out_shifted_strike      ,
	const std::vector<double> & bonds_T0        ,
	const std::vector<double> & libor_shifts    ,
	const std::vector<size_t> & floatingIndices ,
	const double              & annuity_T0)const
{
	//-- Compute shifted swap rate and shifted strike 
	double swap_shift = 0.0;

	for (auto i : floatingIndices)
	swap_shift +=  omega0(i-1,annuity_T0,bonds_T0)*libor_shifts[i-1]; //-- Check the index

	out_shifted_swapRate_T0 += swap_shift;
	out_shifted_strike += swap_shift;	
}


double LmmApproxVanillaSwaptionPricer::computeRebonatoVolatility(
	const Array& x,
	size_t swapStartDateIndex, 		                             
	const double & shifted_swapRate_T0,
	const double & annuity_T0   , 
	const std::vector<size_t> & floatingIndices,
	const std::vector<double> & bonds_T0       ,
	const std::vector<double> & libors_T0      ,
	const std::vector<double> & libor_shifts) const
{
	std::cout<<"  LmmApproxVanillaSwaptionPricer::computeRebonatoVolatility   is to be defined"<<std::endl;

	//	double T_maturity = tenorDates_[swapStartDateIndex];
	//-- Compute vol under swap measure
	double vol_squared = 0.;
		
	// ctntodo uncomment this part of function
	/*
	for (auto i : floatingIndices) 
	{
		double Ti = tenorDates_[i-1];
		for (auto j : floatingIndices)
		{
			double Tj = tenorDates_[j-1];
			double volTmp = vol_->covIntegral(x,i-1,j-1,Ti,Tj,0,T_maturity);
			vol_squared += omega0(i-1,annuity_T0,bonds_T0) * omega0(j-1,annuity_T0,bonds_T0) * (libors_T0[i-1]+libor_shifts[i-1]) * (libors_T0[j-1] +libor_shifts[j-1])* volTmp;
		}
	}

	vol_squared /= (shifted_swapRate_T0*shifted_swapRate_T0);
	
	*/
	return vol_squared;
}

double LmmApproxVanillaSwaptionPricer::omega0(size_t i, const double& annuity_T0, const std::vector<double>& bonds_T0) const
{
	//double per = (tenorDates_[i+1] - tenorDates_[i]);
	const double& per = lmm_->get_LMMTenorStructure()->get_deltaT(i);
	double res = per * bonds_T0[i+1];
	return res/annuity_T0;
}


//LmmApproxSwaptionPricer::SwaptionApproximation(const SwaptionApproximation& approximation)
//{
//	throw("Error: copy cosntructor no implememted");
//	//swapStartDateIndex_ = approximation.swapStartDateIndex_;
//	//swapEndDateIndex_ = approximation.swapEndDateIndex_;
//	//vol_ = approximation.vol_;
//	//tenorDates_ = approximation.tenorDates_;
//}
//


//
////! suppose: T_0 = 0, ZC[i] = P(T_0,T_i) = P(0,T_i), so ZC[0] = 1.0
//double LmmApproxSwaptionPricer::omega0(size_t indexLibor, 
//									   double annuity_T0, 
//									   const std::vector<double>& ZC) 
//{
//	//double deltaT = (tenorDates_[i+1] - tenorDates_[i]);
//	//double res = per * bonds_T0[i+1];
//	//return res/annuity_T0;
//
//	double floatingLeg = lmmTenorStrucutre_.get_deltaT(indexLibor);
//	double fixingleg   = 
//}
//
//
//

//
//
//double LmmApproxSwaptionPricer::computeRebonatoVolatility(size_t swapStartDateIndex, 		                                        
//	                                            double shifted_swapRate_T0,
//	                                            double annuity_T0, 
//												const std::vector<size_t>& floatingIndices,
//												const std::vector<double>& bonds_T0,
//												const std::vector<double>& libors_T0,
//												const std::vector<double>& libor_shifts)
//{
//	double T_maturity = tenorDates_[swapStartDateIndex];
//	//-- Compute vol under swap measure
//	double vol_squared = 0.;
//
//	for each (size_t i in floatingIndices) 
//	{
//		double Ti = tenorDates_[i-1];
//		for each (size_t j in floatingIndices)
//		{
//			double Tj = tenorDates_[j-1];
//			double volTmp = vol_->covIntegral(i-1,j-1,Ti,Tj,0,T_maturity);
//			vol_squared += omega0(i-1,annuity_T0,bonds_T0) * omega0(j-1,annuity_T0,bonds_T0) * (libors_T0[i-1]+libor_shifts[i-1]) * (libors_T0[j-1] +libor_shifts[j-1])* volTmp;
//		}
//	}
//
//	vol_squared /= (shifted_swapRate_T0*shifted_swapRate_T0);
//
//	return vol_squared;
//}
//
//
//
////-- Squared volatility from Rebonato's approx is an out parameter
//double LmmApproxSwaptionPricer::RebonatoApprox(size_t swapStartDateIndex,
//	                                 double strike,
//									 const std::vector<size_t>& floatingIndices,
//	                                 double& out_vol_squared,
//	                                 double swapRate_T0, 
//									 double annuity_T0, 
//									 const std::vector<double>& bonds_T0,
//									 const std::vector<double>& libors_T0,
//									 const std::vector<double>& libor_shifts)
//{ 
//	
//	//double strike = (vanillaSwaption.getUnderlyingSwap()).get_strike();
//	
//	//-- In case swap starts at time 0
//	if (swapStartDateIndex == 0) 
//	{
//		return annuity_T0*std::max(swapRate_T0-strike,0.);
//	}
//	else 
//	{
//		//-- Compute shifted swap rate and shifted strike 
//		double swap_shift = 0.0;
//		for each (size_t i in floatingIndices)
//			swap_shift +=  omega0(i-1,annuity_T0,bonds_T0)*libor_shifts[i-1]; //-- Check the index
//		
//		double shifted_swapRate_T0 = swapRate_T0 + swap_shift;
//		double shifted_strike = strike + swap_shift;
//
//		//-- Compute vol under swap measure
//		double T_maturity = tenorDates_[swapStartDateIndex];
//		out_vol_squared = 0.;
//		for each (size_t i in floatingIndices) 
//		{
//			double Ti = tenorDates_[i-1];
//			for each (size_t j in floatingIndices)
//			{
//				double Tj = tenorDates_[j-1];
//				double volTmp = vol_->covIntegral(i-1,j-1,Ti,Tj,0,T_maturity);
//				out_vol_squared += omega0(i-1,annuity_T0,bonds_T0) * omega0(j-1,annuity_T0,bonds_T0) * (libors_T0[i-1]+libor_shifts[i-1]) * (libors_T0[j-1] +libor_shifts[j-1])* volTmp;
//			}
//		}
//
//		out_vol_squared /= (shifted_swapRate_T0*shifted_swapRate_T0);
//		
//		//-- Apply Black formula
//		NumericalMethods blackCapletPricer;
//		double price = blackCapletPricer.BlackFormula(shifted_swapRate_T0,shifted_strike,out_vol_squared,annuity_T0);
//
//		return price;
//	}
//}
//
//
//double LmmApproxSwaptionPricer::Rebonato_SwaptionPrice(NumericalMethods& NM,
//	                                         double swapRate_T0, 
//											 double strike, 
//											 double vol_squared, 
//											 double annuity)
//{
//	return NM.BlackFormula(swapRate_T0,strike,vol_squared,annuity);
//}
//
//double LmmApproxSwaptionPricer::AndersenApprox() {return 0.;}
//
//
//const std::vector<double>& LmmApproxSwaptionPricer::getTenorDates() {return tenorDates_;}
