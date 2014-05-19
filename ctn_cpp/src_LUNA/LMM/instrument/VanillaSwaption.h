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
	Name::indexInLMMTenorStructure indexMaturity_;
public:

	VanillaSwaption(const LMM::VanillaSwap& vanillaSwap,
					OptionType::OptionType vanillaSwaptionType,
					Name::indexInLMMTenorStructure  indexMaturity)
					:vanillaSwap_(vanillaSwap),
					 vanillaSwaptionType_(vanillaSwaptionType),
					 indexMaturity_(indexMaturity)
	{
		assert(indexMaturity == vanillaSwap_.get_indexStart());
	}

	const LMM::VanillaSwap& getUnderlyingSwap() const { return vanillaSwap_;}
	Name::indexInLMMTenorStructure get_indexMaturity() const {return indexMaturity_;}
	double payoff(double pvVloatingLeg, double pvFixedLeg) const;
	
};

typedef boost::shared_ptr<VanillaSwaption> VanillaSwaption_PTR;


#endif /* LMM_INSTRUMENT_VANILLA_SWAPTION_H */