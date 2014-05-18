#pragma once

#include <boost/shared_ptr.hpp>

#include <LMM/instrument/VanillaSwap.h>
//#include <LMM/instrument/LMMTenorStructure.h>


namespace VanillaSwaptionType
{
	enum VanillaSwaptionType {CALL, PUT};
}

class VanillaSwaption
{
private:
	LMM::VanillaSwap vanillaSwap_;              // The underlying swap, indexStart is the payement date.
	VanillaSwaptionType::VanillaSwaptionType vanillaSwaptionType_;
	Name::indexInLMMTenorStructure indexMaturity_;
public:

	VanillaSwaption(const LMM::VanillaSwap& vanillaSwap,
					VanillaSwaptionType::VanillaSwaptionType vanillaSwaptionType,
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
