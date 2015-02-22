/*!
 * Selection.h
 */
#ifndef SELECTION_H
#define SELECTION_H

#include <vector>
#include <list>
#include <iostream>

/*! Class define interface for Selection
 */
class Selection
{
public:
	// for k-th selection problem
	Selection(unsigned int K);

	void updateData(const std::vector<int>& buffer);

	// get the order statistics (smaller or equal K)
	int get_OrderStatistic(unsigned int k) const;

	friend std::ostream& operator<<(std::ostream& os, const Selection& selection);
private :
	const unsigned int MEMORY_BOUND_;

	std::list<int> memory_;

	// check if element A is addable into the memory
	void updateMemory(const int key);
};
#endif /* SELECTION_H */
