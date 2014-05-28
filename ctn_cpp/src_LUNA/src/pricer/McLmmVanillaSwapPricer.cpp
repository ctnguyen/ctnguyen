#include <cassert>
#include <iostream>
#include <cmath>

#include <LMM/pricer/MCLmmVanillaSwapPricer.h>
#include <LMM/ModelMCLMM/LMMTenorStructure.h>

double MCLmmVanillaSwapPricer::swapRate(const LMM::VanillaSwap& vanillaSwap, size_t nbSimulation) const
{
	throw("Error: not implemented");
	precalculate(vanillaSwap);
	return 0.0;
}

double MCLmmVanillaSwapPricer::swapNPV(const LMM::VanillaSwap& vanillaSwap, size_t nbSimulation)  const
{
	precalculate(vanillaSwap);
	double result = 0.0;

	//!
	double variance = 0.0;

	Name::indexInLMMTenorStructure indexValuationDate = 0;

	for(size_t itrSimulation=0; itrSimulation<nbSimulation; ++itrSimulation)
	{
		mcLmm_->simulateLMM();  // YY TODO: not efficient at all, don't need to do all the simulation ... 
		double npvFloatingLeg = pvFloatingLeg(indexValuationDate, vanillaSwap, mcLmm_->get_numeraire(), mcLmm_->get_liborMatrix());
		double npvFixedLeg    = pvFixedLeg   (indexValuationDate, vanillaSwap, mcLmm_->get_numeraire());
		double npvSwap		  = npvFloatingLeg - npvFixedLeg;
		result				 += npvSwap;
		variance += npvSwap*npvSwap;
	}

	variance /=nbSimulation;
	variance -= result/nbSimulation;
	std::cout << "mcScheme=" << MCSchemeType::mcSchemeType2String(mcLmm_->get_mcSchemeType())<< ", nbSimualtion = " << nbSimulation <<  ",  99% confidential interval = " << 2.57/std::sqrt(variance * nbSimulation) << std::endl;

	return result/nbSimulation;
}


//void MCLmmVanillaSwapPricer::precalculate(const VanillaSwap& vanillaSwap) const
//{
//	const LMMTenorStructure& lmmTenorStructure = mcLmm_->get_LMMTenorStructure();
//
//	assert(lmmTenorStructure.get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;
//	//! YY TODO: need to implement the == operator for enum TenorType
//	//assert(lmmTenorStructure.get_tenorType() == vanillaSwap.get_simulationTenorType());
//
//	//! floatingLeg
//	const std::vector<Name::indexInLMMTenorStructure>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
//	floatingLegTenorLmmTenorRatio_ = vanillaSwap.get_floatingLegTenorLmmTenorRatio();
//	deltaTFloatingLeg_ = std::vector<double>(floatingLegPaymentIndexSchedule.size());
//	for(size_t itr = 0; itr<deltaTFloatingLeg_.size(); ++itr)
//	{
//		size_t index = floatingLegPaymentIndexSchedule[itr];
//		double t2 = lmmTenorStructure.get_tenorDate(index);
//		double t1 = lmmTenorStructure.get_tenorDate(index/floatingLegTenorLmmTenorRatio_-1);
//		deltaTFloatingLeg_[itr] = t2-t1;
//	}	
//	
//	//! fixedLeg
//	const std::vector<Name::indexInLMMTenorStructure>& fixedLegPaymentIndexSchedule    = vanillaSwap.get_fixedLegPaymentIndexSchedule();
//	fixedLegTenorLmmTenorRatio_    = vanillaSwap.get_fixedLegTenorLmmTenorRatio();  
//	deltaTFixedLeg_    = std::vector<double>(fixedLegPaymentIndexSchedule.size());
//	for(size_t itr = 0; itr<deltaTFixedLeg_.size(); ++itr)
//	{
//		size_t index = fixedLegPaymentIndexSchedule[itr];
//		double t2 = lmmTenorStructure.get_tenorDate(index);
//		double t1 = lmmTenorStructure.get_tenorDate(index-fixedLegTenorLmmTenorRatio_);
//		deltaTFixedLeg_[itr] = t2-t1;
//	}
//
//}


//! for one simulation: suppose LMMTenorStructure.data[0] = 0.0
double MCLmmVanillaSwapPricer::pvFloatingLeg(Name::indexInLMMTenorStructure indexValuationDate,
											 const LMM::VanillaSwap& vanillaSwap,
										     const std::vector<double>& numeraire, //numeraire[i]: numeraire value at T_i
									         const matrix& liborMatrix) const
{
	assert(indexValuationDate <= vanillaSwap.get_indexStart()); //YY TODO: this test too slow, esp: within MC simulation
	assert(lmmTenorStructure_->get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;

	double price = 0.0;
	const std::vector<Name::indexInLMMTenorStructure>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//std::vector<Name::indexInLMMTenorStructure>& fixedLegPaymentIndexSchedule    = vanillaSwap.get_fixedLegPaymentIndexSchedule();
	for(size_t itr = 0; itr < floatingLegPaymentIndexSchedule.size(); ++itr)
	{
		//! At time T_{i+1}, pay: L_i(T_i)
		size_t floatingLegPaymentIndex = floatingLegPaymentIndexSchedule[itr]; // = i+1
		//! YY TODO: restriction, Attention: this line suppose: MCLMM simulation use the same lmmTenor to simulate libor !!!
		size_t indexLibor = floatingLegPaymentIndex-1; // eg: = i, when floatingTenor = lmmTenor
		size_t indexT     = indexLibor;                                        // = i
		double libor      = liborMatrix(indexLibor, indexT);
		double delta_T    = deltaTFloatingLeg_[itr];
		price			 += delta_T*libor*numeraire[indexValuationDate]/numeraire[floatingLegPaymentIndex];		
	}
	return price;
}


//double MCLmmVanillaSwapPricer::annuity( Name::indexInLMMTenorStructure indexValuationDate,
//										const VanillaSwap& vanillaSwap,
//									    const std::vector<double>& numeraire) const
//{
//	assert(indexValuationDate <= vanillaSwap.get_indexStart()); //YY TODO: this test too slow, esp: within MC simulation
//	assert(lmmTenorStructure_.get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;
//
//	double price = 0.0;
//	const std::vector<Name::indexInLMMTenorStructure>& fixedLegPaymentIndexSchedule  = vanillaSwap.get_fixedLegPaymentIndexSchedule();
//	for(size_t itr = 0; itr < fixedLegPaymentIndexSchedule.size(); ++itr)
//	{
//		size_t fixedLegPaymentIndex = fixedLegPaymentIndexSchedule[itr]; // = i+1
//		double delta_T              = deltaTFixedLeg_[itr];
//		//std::cout << "numeraire[indexValuationDate]/numeraire[fixedLegPaymentIndex] = " << numeraire[indexValuationDate]/numeraire[fixedLegPaymentIndex] << std::endl;
//		price			           += delta_T*numeraire[indexValuationDate]/numeraire[fixedLegPaymentIndex];		
//	}
//	return price;
//}
//
//double MCLmmVanillaSwapPricer::pvFixedLeg(Name::indexInLMMTenorStructure indexValuationDate,
//	                                      const VanillaSwap& vanillaSwap,
//									      const std::vector<double>& numeraire)  const
//{
//	assert(indexValuationDate <= vanillaSwap.get_indexStart()); //YY TODO: this test too slow, esp: within MC simulation
//	assert(lmmTenorStructure_.get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;
//
//	return vanillaSwap.get_strike()*annuity(indexValuationDate,vanillaSwap,numeraire);
//}
//
