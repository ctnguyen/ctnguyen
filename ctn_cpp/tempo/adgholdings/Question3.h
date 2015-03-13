/*!
 * Question3.h
 */
#ifndef QUESTION3_H
#define QUESTION3_H

#include <iostream>
#include <vector>
#include <random>

namespace Q3
{
	const unsigned int NB_DATA = 10000000;

	// get max profit comes down to track max price and min price from 
	// a prices data
	unsigned int GetMaxProfit(const std::vector<int>& price_data)
	{
		// a small optimization when tracking max min at the same time, see Algorithm ThomasH.Cormen 9.1
		const size_t data_size = price_data.size();
		assert(data_size > 1);// hypothese data has more than 1 element

		int max_tracker = -1000000; int min_tracker = 100000000; // initialize to absurd values
		unsigned int ii = 1;
		while (ii < data_size)
		{
			const int& data_i = price_data[ii-1];
			const int& data_ii = price_data[ii];

			if (data_i < data_ii)
			{
				if (min_tracker > data_i ) min_tracker = data_i;
				if (max_tracker < data_ii) max_tracker = data_ii;
			}
			else
			{
				if (min_tracker > data_ii) min_tracker = data_ii;
				if (max_tracker < data_i) max_tracker = data_i;
			}

			++ii;
			if (ii + 1 < data_size) ++ii;
		}

		return (max_tracker-min_tracker);
	}

	// HELPER FUNCTIONS
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	// function to generate the test, not need to be high performance
	std::vector<int> generate_data()
	{
		std::vector<int> price_data;
		
		// randomly generate the prices data
		const int MIN_BOUND_PRICE = 10 ; const int MAX_BOUND_PRICE = 1000;
		std::random_device rd ;	std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(MIN_BOUND_PRICE, MAX_BOUND_PRICE);

		for (unsigned int i = 0; i < NB_DATA; ++i)
		{
			price_data.push_back(dist(mt));
		}

		assert(price_data.size() == NB_DATA);
		return price_data;
	}

	void PrintData(const std::vector<int>& price_data)
	{
		for (size_t i = 0; i < price_data.size(); ++i)
		{
			std::cout << price_data[i] << std::endl;
		}
	};
}
#endif /* QUESTION3_H */

