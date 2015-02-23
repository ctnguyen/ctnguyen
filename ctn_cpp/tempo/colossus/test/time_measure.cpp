#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
#include <fstream>
#include <algorithm>

#include "helper.h"
#include "DataStream.h"
#include "Selection.h"
#include "Median.h"


struct TimeMeasure
{
	TimeMeasure(int maxN, int stepSize = 0)
	{
		int step;
		if (stepSize == 0)step = maxN / 10; else step = stepSize;

		int counter = step;
		while (counter < maxN)
		{
			sizeList.push_back(counter);
			counter += step;
		}
	}

	std::vector<double> timeSelectionList;
	std::vector<double> timeMedianList;
	std::vector<double> timeStdSortList;
	std::vector<int> sizeList;
};


int main()
{
	const int MAX_N = 10000000;
	const unsigned int k = 10;

	TimeMeasure output(MAX_N);

	std::cout << output.sizeList << std::endl;

	for (size_t i = 0; i < output.sizeList.size(); ++i)
	{
		const unsigned int N = output.sizeList[i];
		std::cout << "- Problem of size N="<<N << std::endl;
		// run for std::sort vector
		{
			SampleDataStream datastream(N);

			std::vector<int> offline_data = datastream.get_OfflineData();



			clock_t start_minimizer = std::clock();
			std::sort(offline_data.begin(),offline_data.end());
			clock_t end_minimizer = std::clock();

			double sort_time = double(end_minimizer - start_minimizer) / CLOCKS_PER_SEC;
			output.timeStdSortList.push_back(sort_time );
			std::cout << "		Finished std::sort Time="<<sort_time << std::endl;
		}

		// run for selection algorithm
		{
			SampleDataStream datastream(N);
			Selection selection(k);

			clock_t start_minimizer = std::clock();
			while (!datastream.isEnd())
			{
				datastream.fetchData();
				const std::vector<int>& buffer = datastream.get_DataBuffer();

				selection.updateData(buffer);
			}
			clock_t end_minimizer = std::clock();

			double selection_time = double(end_minimizer - start_minimizer) / CLOCKS_PER_SEC;
			output.timeSelectionList.push_back(selection_time);
			std::cout << "		Finished Seleciton Time="<<selection_time << std::endl;
		}

		// run for median algorithm
		{
			SampleDataStream datastream(N);
			Median median;

			clock_t start_minimizer = std::clock();
			while (!datastream.isEnd())
			{
				datastream.fetchData();
				const std::vector<int>& buffer = datastream.get_DataBuffer();
				median.updateData(buffer);
			}
			clock_t end_minimizer = std::clock();

			double median_time = double(end_minimizer - start_minimizer) / CLOCKS_PER_SEC;
			output.timeMedianList.push_back(median_time);

			std::cout << "		Finished Median Time="<<median_time << std::endl;
		}

	}//////// end for loop
	
	assert(output.timeSelectionList.size() == output.timeMedianList.size());
	assert(output.timeMedianList.size() == output.sizeList.size());

	std::ofstream outFile;
	outFile.open("output_time_measure.csv");

	outFile <<"Size,	"<<"std::sort,	"<<"Select,	" <<"Median,	" << std::endl;
	for (size_t i = 0; i < output.sizeList.size(); ++i)
	{
		outFile << output.sizeList[i]<< ",	" 
				<< output.timeStdSortList[i] << ",	"
				<< output.timeSelectionList[i] << ",	"
				<< output.timeMedianList[i]    << ",	" << std::endl;
	}
	
	outFile.close();


	return 0;
}
