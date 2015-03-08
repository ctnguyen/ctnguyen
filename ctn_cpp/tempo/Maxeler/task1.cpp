#include <iostream>

#include "VMimage.h"

int main(int argc, char ** argv)
{
	const char* file_path_name = "task1.bin";
	//const char* file_path_name = "test_data\\test01.bin";
	//const char* file_path_name = "prog.ilk";

	if (argc == 2)
	{
		file_path_name = argv[1];
	}

	VMimage data;
	
	try
	{
		data.load(file_path_name);

		std::cout << data << std::endl;
	}
	catch (std::string mgs)
	{
		std::cout << mgs << std::endl;
	}

	return 0;
}
