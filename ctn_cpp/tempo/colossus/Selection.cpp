#include <iostream>
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>

#include <cassert>

#include "Selection.h"

Selection::Selection(unsigned int K)
: BUFFER_SIZE_(K)
{
	if (BUFFER_SIZE_ == 0) throw(" Order Statistics has to be at least 1");
}

int Selection::get_OrderStatistic(unsigned int k) const
{
	assert(k <= BUFFER_SIZE_ && k>0);
	
	std::list<int>::const_iterator it = memory_.begin();
	std::advance(it, k-1);

	return *it;
}

void Selection::fetchData(const std::vector<int>& buffer)
{
	const size_t k = buffer.size();
	if (k == 0) throw(" Exception fetched buffer is empty ");

	for (size_t i = 0; i < k; ++i)
	{
		if (memory_.size() < BUFFER_SIZE_)
		{
			memory_.push_back(buffer[i]);
			memory_.sort();
		}
		else
		{
			updateMemory(buffer[i]);
		}		
	}

	assert(memory_.size() <= BUFFER_SIZE_);
}

void Selection::updateMemory(const int key)
{
	assert(memory_.size() == BUFFER_SIZE_);

	std::list<int>::reverse_iterator rit = memory_.rbegin();
	
	while (key < (*rit)  && rit != memory_.rend())
	{
		const int memory_i = (*rit);//ctn for debug
		++rit ; if (rit == memory_.rend()) break;
		const int memory_ii = (*rit);//ctn for debug

		if( key >= (*rit) )
		{			
			memory_.insert(rit.base(), key) ; memory_.pop_back() ;
			rit = memory_.rbegin();// for checking after because the insert erease the rIterator
			break;
		}
	}

	//key smaller than all the memory
	if (rit == memory_.rend())
	{
		memory_.push_front(key) ; memory_.pop_back();
	}
}

std::ostream& operator<<(std::ostream& os, const Selection& s)
{
	for (std::list<int>::const_iterator it = s.memory_.begin(); it != s.memory_.end(); ++it)
	{
		std::cout << *it << "	";
	}
	return os;
}
