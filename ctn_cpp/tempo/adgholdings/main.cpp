#include <iostream>
#include <ctime>
#include <cassert>

#include "Question1.h"
#include "Question2.h"
#include "Question3.h"
#include "Question4.h"

int main(int argc, char ** argv)
{
	// reading the input to identify the question ID
	int QuestionID=1;

	if (argc == 2)
	{
		QuestionID = atoi(argv[1]);
	}
	assert(0 < QuestionID && QuestionID < 5);
	
	// choose to run the specified question
	switch (QuestionID)
	{
	case 1 : {
		std::cout << " Question 1" << std::endl;
		
		std::list<char> res;
		Q1::GetMostUsedCharacters("annoying", res);
		Q1::printList(res); std::cout << std::endl << std::endl;
		Q1::GetMostUsedCharacters("implementation", res);
		Q1::printList(res);
		
		break;
	}
	case 2:{
		std::cout << " Question2" << std::endl;
		
		int m_array[Q2::MAX_NUMBER];
		Q2::RandomlyInitialize(m_array);
		const int dropped_value = Q2::RandomlyDropOneElement(m_array);
		const int found_missing_value = Q2::GetNumberMissing(m_array);
		std::cout << "Dropped Value="<<dropped_value<<"		found value="<<found_missing_value << std::endl;//ctndebug

		break; 
	}
	case 3:{
		std::cout << " Question3" << std::endl;
		break; 
	}
	case 4:{
		std::cout << " Question4" << std::endl;
		break; 
	}
	default:{
			std::cout << " BAD Question" << std::endl;
			break;
	}
	}

	return 0;
}
