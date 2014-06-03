#include <cassert>
#include <cmath>

#include <LMM/instrument/VanillaSwaption.h>


VanillaSwaption::VanillaSwaption(const LMM::VanillaSwap& vanillaSwap, OptionType::OptionType vanillaSwaptionType)
: vanillaSwap_(vanillaSwap)
, vanillaSwaptionType_(vanillaSwaptionType)
{
	
}


const LMM::VanillaSwap& VanillaSwaption::getUnderlyingSwap() const { return vanillaSwap_;}

LMM::Index VanillaSwaption::get_indexMaturity() const {return vanillaSwap_.get_indexStart();}


double VanillaSwaption::payoff(const double& pvVloatingLeg, const double& pvFixedLeg) const
{
	if(vanillaSwaptionType_ == OptionType::CALL)
		return std::max(pvVloatingLeg - pvFixedLeg, 0.0);
	else
		return std::max(pvFixedLeg - pvVloatingLeg, 0.0);
}
