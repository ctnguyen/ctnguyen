#include <iostream>

#include "helper.h"
#include "DataStream.h"
#include "Selection.h"
#include "Median.h"


int main(int argc, char ** argv)
{
	const unsigned int k = 10;

	const char* input_filename = "sample_data_1000.txt";
	
	if (argc == 2)
	{
		input_filename = argv[1];
	}

	Median median_tracker;
	Selection min_set_tracker(k);
	FileStreamReader file_reader(input_filename);

	while (!file_reader.isEnd())
	{

		file_reader.fetchData();
		const std::vector<int>& buffer = file_reader.get_DataBuffer();
	
		median_tracker.updateData(buffer);
		min_set_tracker.updateData(buffer);

		std::cout << "Actual median " << median_tracker.get_Median()<<"	";
		std::cout << "Actual "<<k<<"-th order stat " << min_set_tracker.get_OrderStatistic(k)<<std::endl;
	}
	

	return 0;
}
