#include <iostream>
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>

#include <cstdlib>
#include <cassert>

#include "Median.h"

void Median::updateData(const std::vector<int>& buffer)
{
	for (size_t i = 0; i < buffer.size(); ++i)
	{
		updateMemory(buffer[i]);
	}	
}

int Median::get_Median() const
{
	if (maxHeap_.size() == minHeap_.size()) 
		return maxHeap_.top();
	else if (maxHeap_.size() > minHeap_.size())
		return maxHeap_.top();
	else // (maxHeap_.size() < minHeap_.size())
		return minHeap_.top();
}

void Median::updateMemory(const int key)
{
	// http://stackoverflow.com/questions/10657503/find-running-median-from-a-stream-of-integers

	if (maxHeap_.empty())
	{
		maxHeap_.push(key);
	}
	else if (minHeap_.empty())
	{
		const int root_maxHeap = maxHeap_.top();
		if (root_maxHeap <= key)
		{
			minHeap_.push(key);
		}
		else
		{
			minHeap_.push(root_maxHeap);
			maxHeap_.pop();
			maxHeap_.push(key);
		}
	}
	else
	{
		if (key < maxHeap_.top())
		{
			maxHeap_.push(key);
		}
		else if (key > minHeap_.top())
		{
			minHeap_.push(key);
		}
		else
		{
			// key between the two roots
			if (minHeap_.size() < maxHeap_.size())
				minHeap_.push(key);
			else
				maxHeap_.push(key);
		}

		const int maxHeapSize = maxHeap_.size();
		const int minHeapSize = minHeap_.size();

		if (maxHeapSize - minHeapSize == 2)
		{
			minHeap_.push(maxHeap_.top()) ; 
			maxHeap_.pop();
		}
		
		if (minHeapSize - maxHeapSize == 2)
		{
			maxHeap_.push(minHeap_.top());
			minHeap_.pop();
		}

		// axiom of data after rebalancing
		assert(maxHeap_.top() <= minHeap_.top());
		// abs (sizeMax - sizeMin)
		assert((std::max(maxHeap_.size(), minHeap_.size()) - std::min(maxHeap_.size(), minHeap_.size())) < 2);
	}

}


std::ostream& operator<<(std::ostream& os, const Median& median)
{
	os << "maxHeapRoot.";
	
	if (!median.maxHeap_.empty()) 
		os << median.maxHeap_.top();
	
	os << "  |" << median.get_Median() << "|  ";
	
	if(!median.minHeap_.empty()) 
		os<< "minHeapRoot." << median.minHeap_.top();
	return os;
}
