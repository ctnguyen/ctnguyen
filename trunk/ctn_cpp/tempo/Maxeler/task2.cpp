#include <iostream>

#include "VMimage.h"
#include "VMinterpreter.h"

int main(int argc, char ** argv)
{
	const char* file_path_name = "task2.bin";
	//const char* file_path_name = "test_data\\test01.bin";

	if (argc == 2)
	{
		file_path_name = argv[1];
	}

	VMimage data;

	try
	{
		data.load(file_path_name);
		VMinterpreter interpreter(data);
		interpreter.process();				
	}
	catch (std::string mgs)
	{
		std::cout << mgs << std::endl;
	}

	return 0;
}