
//! MClmm price Swap, don't need to be too general !!!  

#pragma once

#include <cassert>
#include <boost/shared_ptr.hpp>

#include <LMM/instrument/VanillaSwap.h>  // Instrument
#include <LMM/ModelMCLMM/McLmm.h>        // Model
#include <LMM/ModelMCLMM/LMMTenorStructure.h>



class VanillaSwapPricer// : public VanillaSwapPricer
{
protected:
	ConstLMMTenorStructure lmmTenorStructure_;
	//const std::vector<double>& liborsInitValue_;

	//! work place: initialized in precalculate()
	//! YY: TODO: these are duplicated in pricer and vanillaSwap class, to remove it from pricer.
	mutable std::vector<double> deltaTFloatingLeg_;
	mutable std::vector<double> deltaTFixedLeg_;
	//mutable size_t floatingLegTenorLmmTenorRatio_; // this one must be one, if not there will be lots of problem! 
	mutable size_t fixedLegTenorLmmTenorRatio_;

public:
	VanillaSwapPricer(ConstLMMTenorStructure lmmTenorStructure)
		: lmmTenorStructure_(lmmTenorStructure)
	{};

protected: 
	//! pre-calculation
	void precalculate(const LMM::VanillaSwap& vanillaSwap) const;

	/*! see Damiano Brigo 2006 (1.24)(1.25)(1.26) ($6.7)  which is C_{\alpha,\beta}(t) in p.240
	 *
	 * C_{\alpha,\beta}(t) = Annuity(t) = \sum \tau_i P(t,T_i) =  \sum \tau_i \frac{P(t,T_i)}{P(t,T_{\alpha})}
	 */
	virtual double annuity( LMM::Index indexValuationDate,
		const LMM::VanillaSwap& vanillaSwap,
		const std::vector<double>& numeraire) const;

	/*! see Damiano Brigo 2006 (1.24)(1.25)(1.26) ($6.7)  which is S_{\alpha,\beta}(t) in p.238
	 *
	 * S_{\alpha,\beta}(t) = \frac{ P(t,T_{\alpha}) - P(t,T_{\beta}) }{  C_{\alpha,\beta}(t)  } 
	 */
	virtual double forwardSwapRate( LMM::Index indexValuationDate,
		const LMM::VanillaSwap& vanillaSwap,
		const std::vector<double>& numeraire) const;

	virtual double pvFixedLeg(LMM::Index indexValuationDate,
		const LMM::VanillaSwap& vanillaSwap,
		const std::vector<double>& numeraire)  const;

	//! YY TODO: maybe move it here, as the fixing leg ...
	//double pvFloatingLeg(LMM::Index indexValuationDate,
	//					const VanillaSwap& vanillaSwap,
	//					const std::vector<double>& numeraire, //numeraire[i]: numeraire value at T_i
	//					const matrix& liborMatrix) const;


public:
	//! To validate the result
	double swapNPV_Analytical_1(const LMM::VanillaSwap& vanillaSwap, const std::vector<double>& liborsInitValue)  const; // initLibor[i] = L_i[T_0]
	double swapNPV_Analytical_2(const LMM::VanillaSwap& vanillaSwap, const std::vector<double>& liborsInitValue)  const; // initLibor[i] = L_i[T_0]

	double swapRate_Analytical(const LMM::VanillaSwap& vanillaSwap,
												  const std::vector<double>& liborsInitValue)  const;
};
