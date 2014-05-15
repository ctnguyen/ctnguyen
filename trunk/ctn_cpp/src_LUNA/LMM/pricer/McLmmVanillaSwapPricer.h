
//! MClmm price Swap, don't need to be too general !!!  

#pragma once
#include <boost/shared_ptr.hpp>
#include <LMM/ModelMCLMM/McLmm.h>        // Model
#include <LMM/instrument/VanillaSwap.h>  // Instrument
#include <LMM/pricer/VanillaSwapPricer.h>


class MCLmmVanillaSwapPricer : public VanillaSwapPricer// want to use the pre-calculation of 
{
protected:
	MCLmm_PTR mcLmm_; // model
public:
	MCLmmVanillaSwapPricer(const MCLmm_PTR& mcLmm)
		: VanillaSwapPricer(mcLmm->get_LMMTenorStructure()), 
		  mcLmm_(mcLmm)
	{};

	//! Pricing at time T0=0
	double swapRate(const VanillaSwap& vanillaSwap, size_t nbSimulation) const;
	double swapNPV (const VanillaSwap& vanillaSwap, size_t nbSimulation)  const;

	//! 
	void resetGeneratorToinitSeed(){mcLmm_->get_RNGenerator()->resetGeneratorToinitSeed();}

protected: 
	//! pre-calculation
	//void precalculate(const VanillaSwap& vanillaSwap) const;

	//! one simulation
	double pvFloatingLeg(Name::indexInLMMTenorStructure indexValuationDate,
						 const VanillaSwap& vanillaSwap,
						 const std::vector<double>& numeraire, 
						 const matrix& libors) const ;

	//double annuity(Name::indexInLMMTenorStructure indexValuationDate,
	//			   const VanillaSwap& vanillaSwap,
	//			   const std::vector<double>& numeraire) const;

	//double pvFixedLeg(Name::indexInLMMTenorStructure indexValuationDate,
	//				  const VanillaSwap& vanillaSwap,
	//				  const std::vector<double>& numeraire) const;

public:
	//! To validate the result
	//double swapNPV_Analytical(const VanillaSwap& vanillaSwap,
	//	const std::vector<double>& initLibor) const;

};
