#include <iostream>

#include "Helper.h"
#include "NodeWord.h"
#include "TextProcess.h"

int main(int argc, char ** argv)
{
	const char* file_path_name = "sampe_text.txt";

	if (argc == 2)
	{
		file_path_name = argv[1];
	}

	
	try
	{
		std::cout<<"read text file and word processing here"<<std::endl;
	}
	catch (std::string& mgs)
	{
		std::cout << "catch opening file exeption" << std::endl;
		std::cout << mgs << std::endl;
	}

	return 0;
}
