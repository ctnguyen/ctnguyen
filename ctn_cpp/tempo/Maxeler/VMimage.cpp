#include "VMimage.h"
#include "Helper.h"

#include <iostream>
#include <fstream>
#include <cassert>

VMimage::VMimage()
: data_size_(-10000) // initiate to an absurb value
, image_size_(-10000)
{

}

helper::Int32 VMimage::size() const
{
	assert(data_size_ == (helper::Int32) data_.size());
	return data_size_;
}

helper::Int32& VMimage::operator[](size_t i)
{
	return data_[i];
}

const helper::Int32& VMimage::operator[](size_t i)const
{
	return data_[i];
}

void VMimage::load(const char* file_path_name)
{
	std::ifstream file_stream;

	file_stream.open(file_path_name, std::fstream::in);
	
	if (file_stream.is_open())
	{
		std::string first_line;
		if (file_stream.good())
		{
			getline(file_stream, first_line);
			data_size_ = helper::convertHexStringToInt32(first_line);
		}

		data_.resize(data_size_);

		// ctntodo subtility from exercice TODO OR NOT??
		/*
		std::string second_line;
		if (file_stream.good())
		{
			getline(file_stream, second_line);		
			image_size_ = helper::convertHexStringToInt32(second_line);
		}		
		*/

		size_t line_counter=0;
		unsigned int nbEmptyLine=0;
		while (file_stream.good())
		{
			std::string line;
			getline(file_stream, line);

			if (!line.empty())
			{
				helper::Int32 int_number = helper::convertHexStringToInt32(line);
				data_[line_counter] = int_number;
				++line_counter;
			}
			else
			{
				//std::cout << "line[" << nbLine << "]  =========================== bad line (empty) " << std::endl;
				++nbEmptyLine;
			}
		}

		if (nbEmptyLine > 1)
		{
			std::cout << " WARNING : File " << file_path_name << " has more than one empty line" << std::endl;
		}
	}
	else
	{
		std::string msg(file_path_name) ; msg += "] is a bad input file -- RUNTIME ERROR";
		throw(msg);
	}

	file_stream.close();
}