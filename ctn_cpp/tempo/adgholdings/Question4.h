/*!
 * Question4.h
 */
#ifndef QUESTION4_H
#define QUESTION4_H

#include <iostream>
#include <list>
#include <algorithm>

namespace Q4
{
	int A[] = {1,-1,3,8,4};
	//int A[] = {1,2,3,4,5};

	void GetMaxSum(int& sum, std::list<int>& res)
	{
		res.clear();
		
		int odd_running_sum=0;
		int even_running_sum=0;

		const unsigned int lenght = (sizeof(A) / sizeof(*A));
		
		// even sum
		for (size_t i = 0; i < lenght; i+=2)
		{
			if (A[i]>0)
				even_running_sum += A[i];
		}

		// odd sum
		for (size_t ii = 1; ii < lenght; ii += 2)
		{
			if (A[ii]>0)
				odd_running_sum += A[ii];
		}

		// all the array are negatives
		// the max negative number is the max sum
		if (odd_running_sum == 0 && even_running_sum == 0)
		{
			sum = *std::max_element(A, A + lenght);			
			res.push_back(sum);
		}
		else if (odd_running_sum > even_running_sum)
		{
			sum = odd_running_sum;
			// push back the list			
			for (size_t ii = 1; ii < lenght; ii += 2)
			{
				if (A[ii]>0) res.push_back(A[ii]);
			}
		}
		else
		{
			sum = even_running_sum;
			// push back the list			
			for (size_t i = 0; i < lenght; i += 2)
			{
				if (A[i]>0)	res.push_back(A[i]);
			}
		}
	}


	// HELPER FUNCTIONS
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	void printList(const std::list<int>& output)
	{
		//ctndebug
		for (std::list<int>::const_iterator it = output.begin(); it != output.end(); ++it)
		{
			std::cout << *it << std::endl;
		}
	}
}
#endif /* QUESTION4_H */

