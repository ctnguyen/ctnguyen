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
	//int A[] = {1,-1,3,8,4};  // 1+8=9
	int A[] = { 1, 2, 3, 4, 5 };   //1+3+5=9
	//int A[] = { 3, 2, 5, 10, 7 }; // 3+5+7

	void GetMaxSum(int& sum, std::list<int>& res)
	{
		res.clear();
		
		int incl = A[0];
		int excl = 0;

		const unsigned int LENGHT = (sizeof(A) / sizeof(*A));
		
		// drop first non positive elements
		size_t start_i = 0;
		while (start_i < LENGHT && A[start_i] <= 0){ ++start_i;  }
		
		size_t parity_index = start_i;
		bool is_even_used;
		int n_excl = 0;
		int n_incl = A[start_i];
		std::list<int> odd_list;
		std::list<int> event_list;
		if (A[start_i] > 0)
		{
			if (start_i % 2 == 0) {
				event_list.push_back(A[start_i]);
				is_even_used = true;
			}
			else{
				odd_list.push_back(A[start_i]);
				is_even_used = false;
			}
		}
		
		++start_i;

		size_t i = start_i;
		while (i < LENGHT)
		{
			const int& current_value = A[i];
			// save old values
			const int o_incl = n_incl;
			const int o_excl = n_excl;
		
			// compute the new max excluding current value
			n_excl = (n_incl > n_excl) ? n_incl : n_excl;
						
			n_incl = (std::max)(o_excl + current_value, o_incl);

			// normally if all values are positive, use i to count the parity
			// But when a negative value occur, the parity has to be switched
			// ctntodo if have more time , may be refactore this potential bug
			if (current_value>0)
				parity_index +=1;
			else
				parity_index +=2;

			if (n_incl > n_excl)
			{				
				if (parity_index % 2 == 0){
					event_list.push_back(current_value);
					is_even_used = true;
				}
				else{
					odd_list.push_back(current_value);
					is_even_used = false;
				}
			}

			++i;
		}

		sum = (n_incl > n_excl) ? n_incl : n_excl;

		if (is_even_used)
			res = event_list;
		else
			res = odd_list;
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

