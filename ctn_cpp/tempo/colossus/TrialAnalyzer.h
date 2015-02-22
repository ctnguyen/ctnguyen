/*!
 * TrialAnalyzer.h
 */
#ifndef TRIALANALYZER_H
#define TRIALANALYZER_H

#include <vector>
#include <iostream>
#include <queue>
#include <functional>

#include "helper.h"

/*! This class use a trivial method , use for testing accurancy of advanced algorithm
 */
class TrialAnalyzer
{
public:
	
	// update the fetched data
	void updateData(const std::vector<int>& buffer);

	int get_OrderStatistic(unsigned int k) const;

	int get_Median() const;

	friend std::ostream& operator<<(std::ostream& os, const TrialAnalyzer& analyzer);

private :
	
	std::vector<int> memory_;
};


#endif /* TRIALANALYZER_H */
