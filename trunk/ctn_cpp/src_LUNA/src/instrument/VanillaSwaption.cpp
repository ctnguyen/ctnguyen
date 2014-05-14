#pragma once

#include <cassert>
#include <cmath>

#include <LMM/instrument/VanillaSwaption.h>

double VanillaSwaption::payoff(double pvVloatingLeg, double pvFixedLeg) const
{
	if(vanillaSwaptionType_ == VanillaSwaptionType::VanillaSwaptionType::CALL)
		return std::max(pvVloatingLeg - pvFixedLeg, 0.0);
	else
		return std::max(pvFixedLeg - pvVloatingLeg, 0.0);
}