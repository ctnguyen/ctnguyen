#pragma once

#include <cassert>

#include <LMM/Name.h>
#include <LMM/instrument/TenorType.h>

class Caplet
{
private:
	double strike_;

	Name::indexInLMMTenorStructure indexFixing_;      
	Name::indexInLMMTenorStructure indexPayement_;   
	Tenor   underlyingLiborTenorType_;
	Tenor   lmmTenorStructureTenorType_; // used to check pricer's tenor type

public:
	Caplet(double strike,
		Name::indexInLMMTenorStructure  indexFixing, 
		Name::indexInLMMTenorStructure  indexPayement, 
		Tenor    underlyingLiborTenorType,
		Tenor    lmmTenorStructureTenorType)
		:indexFixing_(indexFixing), 
		 indexPayement_(indexPayement), 
		 underlyingLiborTenorType_(underlyingLiborTenorType), 
		 lmmTenorStructureTenorType_(lmmTenorStructureTenorType)
	{
		assert( underlyingLiborTenorType_ == lmmTenorStructureTenorType_);
	}
};
