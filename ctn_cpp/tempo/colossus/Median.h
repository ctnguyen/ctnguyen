/*!
 * Median.h
 */
#ifndef MEDIAN_H
#define MEDIAN_H

#include <vector>
#include <iostream>
#include <queue>

#include "helper.h"

/*! 
 */
class Median
{
public:
	
	// update the fetched data
	void updateData(const std::vector<int>& buffer);

	// get the median :
	// if odd number of data elements, give the effective median
	// if even number of data elements, give the lowe median
	int get_Median() const;

	friend std::ostream& operator<<(std::ostream& os, const Median& median);

private :

	std::priority_queue<int> maxHeap_;
	std::priority_queue<int, std::vector<int>, helper::Greater > minHeap_;

	// add an element to the data memory : max heap or mean heap
	void updateMemory(const int key);
};


#endif /* MEDIAN_H */
