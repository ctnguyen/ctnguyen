#include <iostream>
#include <ctime>

#include "Helper.h"
#include "NodeWord.h"
#include "TextProcess.h"

int main(int argc, char ** argv)
{
	//const char* file_path_name = "sampe_text.txt";
	const char* file_path_name = "referece_text.txt";

	if (argc == 2)
	{
		file_path_name = argv[1];
	}

	// ctntodo handle exception of opening binary file
	try
	{
		std::ifstream file_stream;
		file_stream.open(file_path_name, std::ios::in);

		if (file_stream.is_open())
		{
			Word word;
			TextProcess textprocess;
			unsigned int nbWord = 0;

			clock_t start_reading = std::clock();
			while (file_stream.good())
			{
				file_stream >> word;
				if (!word.empty())
				{
					++nbWord; //if (!word.empty()) std::cout << word << std::endl;//ctndebug
					textprocess.add_Word(word);
				}
			}
			clock_t end_reading = std::clock();
			double reading_time = double(end_reading - start_reading) / CLOCKS_PER_SEC;

			Result res;
			clock_t start_res = std::clock();
			textprocess.get_Result(res);
			clock_t end_res = std::clock();
			double res_time = double(end_reading - start_reading) / CLOCKS_PER_SEC;

			//std::cout << textprocess << std::endl;//ctndebug
			std::cout << res << std::endl;//ctndebug
			std::cout << "Number word=" << nbWord << "	reading time=" << reading_time << "	result_time=" << res_time << std::endl;//ctndebug
		}

		file_stream.close();
	}
	catch (...)
	{
		std::cout << "catch opening file exeption" << std::endl;
	}

	return 0;
}
