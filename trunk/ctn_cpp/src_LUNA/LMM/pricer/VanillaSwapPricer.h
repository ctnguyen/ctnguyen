#ifndef LMM_PRICER_VANILLASWAPPRIER_H
#define LMM_PRICER_VANILLASWAPPRIER_H
#pragma once

#include <LMM/instrument/VanillaSwap.h> 
#include <LMM/helper/LMMTenorStructure.h>

/*! \class VanillaSwapPricer
* SwapPricer with exact formula, don't need MonteCarlo
*/
class VanillaSwapPricer
{

public:

	VanillaSwapPricer(ConstLMMTenorStructure lmmTenorStructure);

	//! To validate the result

	// initLibor[i] = L_i[T_0]
	double swapNPV_Analytical_1(const LMM::VanillaSwap& vanillaSwap, const std::vector<double>& liborsInitValue)  const;

	// initLibor[i] = L_i[T_0]
	double swapNPV_Analytical_2(const LMM::VanillaSwap& vanillaSwap, const std::vector<double>& liborsInitValue)  const;

	double swapRate_Analytical(const LMM::VanillaSwap& vanillaSwap,  const std::vector<double>& liborsInitValue)  const;

protected: 

	/*! see Damiano Brigo 2006 (1.24)(1.25)(1.26) ($6.7)  which is C_{\alpha,\beta}(t) in p.240
	*
	* C_{\alpha,\beta}(t) = Annuity(t) = \sum \tau_i P(t,T_i) =  \sum \tau_i \frac{P(t,T_i)}{P(t,T_{\alpha})}
	*/
	virtual double annuity( 
		const LMM::Index            indexValuationDate,
		const LMM::VanillaSwap    & vanillaSwap,
		const std::vector<double> & numeraire
		) const;

	/*! see Damiano Brigo 2006 (1.24)(1.25)(1.26) ($6.7)  which is S_{\alpha,\beta}(t) in p.238
	*
	* S_{\alpha,\beta}(t) = \frac{ P(t,T_{\alpha}) - P(t,T_{\beta}) }{  C_{\alpha,\beta}(t)  } 
	*/
	virtual double forwardSwapRate( 
		const LMM::Index            indexValuationDate,
		const LMM::VanillaSwap    & vanillaSwap,
		const std::vector<double> & numeraire
		) const;

	virtual double pvFixedLeg(
		const LMM::Index            indexValuationDate,
		const LMM::VanillaSwap    & vanillaSwap,
		const std::vector<double> & numeraire
		)  const;

	//! YY TODO: maybe move it here, as the fixing leg ...
	//double pvFloatingLeg(LMM::Index indexValuationDate,
	//					const VanillaSwap& vanillaSwap,
	//					const std::vector<double>& numeraire, //numeraire[i]: numeraire value at T_i
	//					const matrix& liborMatrix) const;

protected:

	ConstLMMTenorStructure lmmTenorStructure_;	
};

#endif /* LMM_PRICER_VANILLASWAPPRIER_H */