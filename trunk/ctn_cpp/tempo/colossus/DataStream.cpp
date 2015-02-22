#include <iostream>
#include <random>
#include <fstream>
#include <sstream>

#include <cassert>

#include "DataStream.h"

SampleDataStream::SampleDataStream(const char* filename)
: counter_(0)
{
	//std::cout << "File Name [" << filename <<"]"<< std::endl;

	std::ifstream instream;
	instream.open(filename);

	if (instream.is_open())
	{

		while (instream.good())
		{
			std::string line;
			getline(instream, line);

			if (!line.empty() && line.at(0) != '#') // line start with # is a comment
			{
				//std::cout << line << std::endl;

				std::string cell;
				std::vector<std::string> cell_array;
				std::stringstream line_stream(line);

				while (getline(line_stream, cell, ' '))
				{
					cell_array.push_back(cell);
				}
				
				for (size_t i = 0; i < cell_array.size(); ++i)
				{
					offline_data_.push_back(atoi(cell_array[0].c_str()));
				}
			}
			else
			{
				std::cout << line << std::endl; 
			}
		}
	}
	else
	{
		std::cout << filename << " - File not found " << std::endl; 
	}

	instream.close();

	new_data_buffer_.resize(1);
}

SampleDataStream::SampleDataStream(unsigned int N)
: counter_(0)
{
	const int MAX_DATA = 1000000;
	const int MIN_DATA = -1000000;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(MIN_DATA, MAX_DATA);

	for (unsigned int i = 0; i < N; ++i)
	{
		offline_data_.push_back( dist(mt) );
	}

	new_data_buffer_.resize(1);
}

SampleDataStream::~SampleDataStream(){}

bool SampleDataStream::isEnd() const
{
	return counter_ == offline_data_.size();
}

void SampleDataStream::fetchData()
{
	new_data_buffer_[0] = offline_data_[counter_];		
	++counter_;
}

const std::vector<int>& SampleDataStream::get_DataBuffer() const
{
	return new_data_buffer_;
}

const std::vector<int>& SampleDataStream::get_OfflineData() const
{
	return offline_data_;
}

void SampleDataStream::write_to_stream(std::ostream& os) const
{
	for (size_t i = 0; i < offline_data_.size(); ++i)
	{
		os << offline_data_[i] << std::endl;
	}
}


std::ostream& operator<<(std::ostream& os, const SampleDataStream& offlinestream)
{
	offlinestream.write_to_stream(os);
	return os;
}