
//! MClmm price Swap, don't need to be too general !!!  

#pragma once
#include <boost/shared_ptr.hpp>
#include "McLmm.h"        // Model
#include "VanillaSwap.h"  // Instrument
#include "LMMTenorStructure.h"
#include <cassert>


class VanillaSwapPricer// : public VanillaSwapPricer
{
protected:
	const LMMTenorStructure lmmTenorStructure_;
	//const std::vector<double>& liborsInitValue_;

	//! work place: initialized in precalculate()
	//! YY: TODO: these are duplicated in pricer and vanillaSwap class, to remove it from pricer.
	mutable std::vector<double> deltaTFloatingLeg_;
	mutable std::vector<double> deltaTFixedLeg_;
	//mutable size_t floatingLegTenorLmmTenorRatio_; // this one must be one, if not there will be lots of problem! 
	mutable size_t fixedLegTenorLmmTenorRatio_;

public:
	VanillaSwapPricer(const LMMTenorStructure& lmmTenorStructure)
		: lmmTenorStructure_(lmmTenorStructure)
	{};

protected: 
	//! pre-calculation
	void precalculate(const VanillaSwap& vanillaSwap) const;

	//! YY TODO: maybe move it here, as the fixing leg ...
	//double pvFloatingLeg(Name::indexInLMMTenorStructure indexValuationDate,
	//					const VanillaSwap& vanillaSwap,
	//					const std::vector<double>& numeraire, //numeraire[i]: numeraire value at T_i
	//					const matrix& liborMatrix) const;


	virtual double annuity( Name::indexInLMMTenorStructure indexValuationDate,
		const VanillaSwap& vanillaSwap,
		const std::vector<double>& numeraire) const;

	virtual double pvFixedLeg(Name::indexInLMMTenorStructure indexValuationDate,
		const VanillaSwap& vanillaSwap,
		const std::vector<double>& numeraire)  const;

public:
	//! To validate the result
	double swapNPV_Analytical_1(const VanillaSwap& vanillaSwap, const std::vector<double>& liborsInitValue)  const; // initLibor[i] = L_i[T_0]
	double swapNPV_Analytical_2(const VanillaSwap& vanillaSwap, const std::vector<double>& liborsInitValue)  const; // initLibor[i] = L_i[T_0]

	double VanillaSwapPricer::swapRate_Analytical(const VanillaSwap& vanillaSwap,
												  const std::vector<double>& liborsInitValue)  const;
};
