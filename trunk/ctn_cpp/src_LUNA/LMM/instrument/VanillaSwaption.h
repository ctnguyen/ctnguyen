#ifndef LMM_INSTRUMENT_VANILLA_SWAPTION_H
#define LMM_INSTRUMENT_VANILLA_SWAPTION_H
#pragma once

#include <boost/shared_ptr.hpp>

#include <LMM/Name.h>
#include <LMM/instrument/VanillaSwap.h>


class VanillaSwaption
{
private:
	LMM::VanillaSwap vanillaSwap_;              // The underlying swap, indexStart is the payement date.
	OptionType::OptionType vanillaSwaptionType_;
	LMM::Index indexMaturity_;
public:

	VanillaSwaption(const LMM::VanillaSwap& vanillaSwap,
					OptionType::OptionType vanillaSwaptionType,
					LMM::Index indexMaturity);

	const LMM::VanillaSwap& getUnderlyingSwap() const { return vanillaSwap_;}
	
	LMM::Index get_indexMaturity() const {return indexMaturity_;}
	
	double payoff(const double& pvVloatingLeg, const double& pvFixedLeg) const;
	
};

typedef boost::shared_ptr<VanillaSwaption> VanillaSwaption_PTR;


#endif /* LMM_INSTRUMENT_VANILLA_SWAPTION_H */