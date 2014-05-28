#include <cassert>
#include <cmath>

#include <LMM/instrument/VanillaSwaption.h>


VanillaSwaption::VanillaSwaption(const LMM::VanillaSwap& vanillaSwap,
								 OptionType::OptionType vanillaSwaptionType,
								 LMM::Index indexMaturity)
								 : vanillaSwap_(vanillaSwap)
								 , vanillaSwaptionType_(vanillaSwaptionType)
								 , indexMaturity_(indexMaturity)
{
	assert(indexMaturity == vanillaSwap_.get_indexStart());
}


double VanillaSwaption::payoff(const double& pvVloatingLeg, const double& pvFixedLeg) const
{
	if(vanillaSwaptionType_ == OptionType::CALL)
		return std::max(pvVloatingLeg - pvFixedLeg, 0.0);
	else
		return std::max(pvFixedLeg - pvVloatingLeg, 0.0);
}
