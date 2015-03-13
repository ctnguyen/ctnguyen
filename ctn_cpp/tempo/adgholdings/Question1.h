/*!
 * Question1.h
 */
#ifndef QUESTION1_H
#define QUESTION1_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <cctype>

namespace Q1
{
	void GetMostUsedCharacters(const std::string& input, std::list<char>& output)
	{
		output.clear();
		unsigned int max_frequency_counter=1; // counter tracking the max frequency occuring

		std::map<char,unsigned int> map_buffer;
		const size_t str_size = input.size();
		
		// loop through the input string
		for (size_t i = 0; i < str_size; ++i)
		{
			const char& c = input[i];
			if (isalpha(c)) // process iff char is a letter
			{
				char m_char = c;
				if (isupper(c)) m_char = tolower(c); // convert to lower char

				// push the char and increase frequency if already exist
				std::map<char, unsigned int>::iterator it = map_buffer.find(m_char);
				if (it != map_buffer.end())
				{
					++it->second;
					if (max_frequency_counter < it->second) max_frequency_counter = it->second;
				}
				else
				{
					map_buffer[m_char]=1;
				}
			}
		}

		// read out the max frequent char
		for (std::map<char, unsigned int>::const_iterator it = map_buffer.begin(); it != map_buffer.end(); ++it)
		{
			if (it->second == max_frequency_counter)
			{
				output.push_back(it->first);
			}
		}
	};

	// HELPER FUNCTIONS
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	void printList(const std::list<char>& output)
	{
		//ctndebug
		for (std::list<char>::const_iterator it = output.begin(); it != output.end(); ++it)
		{
			std::cout << *it << std::endl;
		}
	}
}
#endif /* QUESTION1_H */

