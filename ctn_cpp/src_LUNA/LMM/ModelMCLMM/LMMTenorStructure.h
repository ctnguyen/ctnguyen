#pragma once

#ifndef LMM_TENOR_STRUCTURE_H
#define LMM_TENOR_STRUCTURE_H

#include <vector>
#include <string>
#include <cassert>
#include <string>

#include <boost/shared_array.hpp>

#include <LMM/Name.h>
#include <LMM/instrument/TenorType.h>

class LMMTenorStructure
{
	const TenorTypeEnum::TenorTypeEnum   tenorType_;      // eg: "6M" // never change, to be constant
	Name::indexInLMMTenorStructure horizon_;        // N 
	std::vector<double>            tenorDates_;     // size = N+2, LMMTenorDates[k] = T_k, k =[0,...,N+1]
	std::vector<double>            tenorDeltaT_;    // size = N+1, LMMTenorDeltaT_[k] = T_{k+1} - T_k, k = [0,...,N]

public:

	LMMTenorStructure(const TenorTypeEnum::TenorTypeEnum&  tenorType, //! User should make sure the coherence.
					  const size_t horizonYear);

	//! getter
	Name::indexInLMMTenorStructure get_horizon() const
	{
		return horizon_;
	}



	const std::vector<double>& get_tenorDate() const
	{
		return tenorDates_;
	}
	double get_tenorDate(size_t index) const
	{
		return tenorDates_[index];
	}


	const std::vector<double>& get_deltaT() const
	{
		return tenorDeltaT_;
	}

	double get_deltaT(size_t index) const
	{
		return tenorDeltaT_[index];
	}


	TenorTypeEnum::TenorTypeEnum get_tenorType() const {return tenorType_;} 
	std::string get_tenorTypeStr() const {tenorType_;} 

	//! equal operator: when modify the class, don't forget to adjust == operator
    bool operator == (const LMMTenorStructure& LMMTenorStructure);

	//! print in Excel
	void print();
};

typedef boost::shared_ptr<LMMTenorStructure> LMMTenorStructure_PTR;

#endif /* LMM_TENOR_STRUCTURE_H */