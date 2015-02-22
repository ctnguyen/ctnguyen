#include <iostream>

#include <cstdlib>
#include <cassert>

#include "TrialAnalyzer.h"

void TrialAnalyzer::updateData(const std::vector<int>& buffer)
{
	memory_.insert(memory_.end(), buffer.begin(), buffer.end());
	std::sort(memory_.begin(),memory_.end());
}

int TrialAnalyzer::get_OrderStatistic(unsigned int k) const
{
	assert( !memory_.empty() && k>0 );

	if (k >= memory_.size())
		return memory_.back();
	else
		return memory_[k-1];
}

int TrialAnalyzer::get_Median() const
{
	assert(!memory_.empty());
	size_t median_position = (memory_.size()-1)/2;
	return memory_[ median_position ];
}

std::ostream& operator<<(std::ostream& os, const TrialAnalyzer& analyzer)
{
	os << analyzer.memory_;

	return os;
}
