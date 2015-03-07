#include <iostream>

#include "VMimage.h"

int main(int argc, char ** argv)
{
	const char* file_path_name = "task1.bin";

	if (argc == 2)
	{
		file_path_name = argv[1];
	}

	VMimage data;
	
	try
	{
		data.load(file_path_name);

		for (size_t i = 0; i < (size_t)data.size(); ++i)
		{
			std::cout << data[i] << std::endl;
		}
	}
	catch (std::string mgs)
	{
		std::cout << mgs << std::endl;
	}

	return 0;
}
