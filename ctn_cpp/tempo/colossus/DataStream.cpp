#include <iostream>
#include <random>
#include <sstream>

#include <cassert>

#include "DataStream.h"


FileStreamReader::FileStreamReader(const char* filename, const unsigned int buffer_size)
	: BUFFER_SIZE_(buffer_size)
	, isEndStream(false)
{
	input_stream_.open(filename);
	if (!input_stream_.is_open())
		isEndStream = true;
}

FileStreamReader::~FileStreamReader()
{
	if (input_stream_.is_open())
		input_stream_.close();
}

bool FileStreamReader::isEnd() const
{
	return isEndStream;
}

void FileStreamReader::fetchData()
{
	assert(!isEndStream);

	data_buffer_.clear();
	unsigned int counter = 0;
	while (input_stream_.good() && counter < BUFFER_SIZE_)
	{
		std::string line;
		getline(input_stream_, line);

		if (!line.empty() && line.at(0) != '#') // line start with # is a comment
		{
			data_buffer_.push_back(atoi(line.c_str()));
			
			++counter;
		}
		else
		{
			std::cout << line << std::endl;
		}		
	}

	if (!input_stream_.good())
	{
		isEndStream = true;
	}
}

const std::vector<int>& FileStreamReader::get_DataBuffer() const
{
	return data_buffer_;
}





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
				offline_data_.push_back(atoi(line.c_str()));
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
		offline_data_.push_back(dist(mt));
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