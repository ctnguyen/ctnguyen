#pragma once
#include "VanillaSwaption.h"
#include <cassert>
#include <cmath>


double VanillaSwaption::payoff(double pvVloatingLeg, double pvFixedLeg) const
{
	if(vanillaSwaptionType_ == VanillaSwaptionType::VanillaSwaptionType::CALL)
		return std::max(pvVloatingLeg - pvFixedLeg, 0.0);
	else
		return std::max(pvFixedLeg - pvVloatingLeg, 0.0);
}