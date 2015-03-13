/*!
 * Question2.h
 */
#ifndef QUESTION2_H
#define QUESTION2_H

#include <iostream>
#include <random>
#include <cassert>

namespace Q2
{
	const unsigned int MAX_NUMBER = 100;

	int GetNumberMissing(const int m_input[MAX_NUMBER])
	{		
		const int total_sum = ((MAX_NUMBER + 1)*MAX_NUMBER)/2;
		
		int running_sum = 0;
		for (size_t i = 0; i < MAX_NUMBER; ++i)
		{
			running_sum+=m_input[i];
		}

		assert(running_sum < total_sum);
		return (total_sum-running_sum);
	};

	int RandomlyDropOneElement(int* m_array)
	{
		// randomly generate the index to be drop then drop out the value
		const int MAX_INDEX = MAX_NUMBER - 1;
		const int MIN_INDEX = 0;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(MIN_INDEX, MAX_INDEX);

		const unsigned int index = (unsigned int)dist(mt);
		assert(index < MAX_NUMBER);
		int dropped_value = m_array[index];
		m_array[index] = 0;
		return dropped_value;
	};

	void RandomlyInitialize(int* m_array)
	{
		// initialize numbers
		for (size_t i = 0; i < MAX_NUMBER; ++i)
		{
			m_array[i] = i + 1;
		}

		// randomly permute the array
		const unsigned int NB_OF_RANDOM_PERMUTATION=100000;
		const int MAX_INDEX = MAX_NUMBER-1;
		const int MIN_INDEX = 0;
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(MIN_INDEX, MAX_INDEX);

		for (unsigned int i = 0; i < NB_OF_RANDOM_PERMUTATION; ++i)
		{
			const unsigned int first_index = (unsigned int)dist(mt);
			const unsigned int second_index = (unsigned int)dist(mt);
			assert(first_index < MAX_NUMBER && second_index < MAX_NUMBER);
			const int buffer = m_array[first_index];
			m_array[first_index]  = m_array[second_index];
			m_array[second_index] = buffer;
		}
	};

	void PrintArray(const int m_input[MAX_NUMBER])
	{
		for (size_t i = 0; i < MAX_NUMBER; ++i)
		{
			std::cout << m_input[i] << std::endl;
		}
	};

}
#endif /* QUESTION2_H */
