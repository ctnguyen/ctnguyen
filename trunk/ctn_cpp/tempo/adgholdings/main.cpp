#include <iostream>
#include <ctime>

#include "Question1.h"
#include "Question2.h"
#include "Question3.h"
#include "Question4.h"

int main(int argc, char ** argv)
{
	int QuestionID=1;

	if (argc == 2)
	{
		QuestionID = atoi(argv[1]);
	}
	std::cout<<" Question"<<QuestionID<<std::endl;

	return 0;
}
