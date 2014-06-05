
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
	: VanillaSwapPricer(mcLmm->get_LMMTenorStructure() )
	, mcLmm_(mcLmm)
	{};

	//! Pricing at time T0=0
	double swapRate(const LMM::VanillaSwap& vanillaSwap, size_t nbSimulation) const;
	double swapNPV (const LMM::VanillaSwap& vanillaSwap, size_t nbSimulation)  const;

	//! 
	void resetGeneratorToinitSeed(){mcLmm_->get_RNGenerator()->resetGeneratorToinitSeed();}

protected: 

	//! one simulation
	double pvFloatingLeg(LMM::Index indexValuationDate,
						 const LMM::VanillaSwap& vanillaSwap,
						 const std::vector<double>& numeraire, 
						 const matrix& libors) const ;

	//double annuity(LMM::Index indexValuationDate,
	//			   const LMM::VanillaSwap& LMM::VanillaSwap,
	//			   const std::vector<double>& numeraire) const;

	//double pvFixedLeg(LMM::Index indexValuationDate,
	//				  const LMM::VanillaSwap& LMM::VanillaSwap,
	//				  const std::vector<double>& numeraire) const;

public:
	//! To validate the result
	//double swapNPV_Analytical(const LMM::VanillaSwap& LMM::VanillaSwap,
	//	const std::vector<double>& initLibor) const;

};
