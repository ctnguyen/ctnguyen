#include <cassert>

#include <LMM/pricer/McLmmVanillaSwaptionPricer.h>

double MCLmmVanillaSwaptionPricer::price(const VanillaSwaption& vanillaSwaption, size_t nbSimulation)  const
{
	VanillaSwap vanillaSwap = vanillaSwaption.getUnderlyingSwap();
	//! YY TODO: need to implement the == operator for enum TenorType
	//assert(vanillaSwap.get_lmmTenorStructureTenorType() == mcLmm_->get_LMMTenorStructure().get_tenorType());
	precalculate(vanillaSwap);
	double result = 0.0;

	//!
	double variance = 0.0;

	Name::indexInLMMTenorStructure indexValuationdate = 0;
	Name::indexInLMMTenorStructure indexMaturity = vanillaSwaption.get_indexMaturity();

	for(size_t itrSimulation=0; itrSimulation<nbSimulation; ++itrSimulation)
	{
		mcLmm_->simulateLMM();  // YY TODO: not efficient at all, don't need to do all the simulation ... 
		const matrix& liborMatrix = mcLmm_->get_liborMatrix();
		const std::vector<double>& numeraire = mcLmm_->get_numeraire();
		double npvFloatingLeg      = pvFloatingLeg(indexMaturity, vanillaSwap, numeraire, liborMatrix);
		double npvFixedLeg         = pvFixedLeg   (indexMaturity, vanillaSwap, numeraire);
		double payoffAtMaturity    = vanillaSwaption.payoff(npvFloatingLeg,npvFixedLeg);
		double value               = payoffAtMaturity * numeraire[indexValuationdate]/numeraire[indexMaturity];
		result					  += value;

		variance += value*value;
	}

	variance /=nbSimulation;
	variance -= result/nbSimulation;
	std::cout << "mcScheme=" << MCSchemeType::mcSchemeType2String(mcLmm_->get_mcSchemeType())<< ", nbSimualtion = " << nbSimulation <<  ",  99% confidential interval = " << 2.57/std::sqrt(variance * nbSimulation) << std::endl;

	return result/nbSimulation;
}