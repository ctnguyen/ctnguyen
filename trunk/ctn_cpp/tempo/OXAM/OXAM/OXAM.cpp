// OXAM.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
//ctn #include <list>
#include <deque>
#include <map>
#include <limits>

#include <cassert>

class Order
{
public:
	Order(unsigned long _time, unsigned int _orderID) :time(_time), orderID(_orderID){}
	const unsigned long time;
	const unsigned orderID;
	virtual bool isErease() const = 0 ;
	virtual bool isInsert() const = 0;
	virtual double price() const = 0;

	bool operator ==(const Order& l) const { return ( orderID == l.orderID ); }
};
std::ostream& operator<<(std::ostream& os, const Order& order);

class EraseOrder : public Order
{
public:
	EraseOrder(unsigned long _time, unsigned int _orderID) :Order(_time,_orderID){}
	virtual bool isErease() const { return true; };
	virtual bool isInsert() const { return false; };
	virtual double price() const { throw("EreaseOrder do not have price"); return -100000; }
};

class InsertOrder : public Order
{
public:
	InsertOrder(unsigned long _time, unsigned int _orderID, const double& _price) 
	: Order(_time, _orderID), price_(_price){}
	
	virtual bool isErease() const { return false ; }
	virtual bool isInsert() const { return true  ; }
	virtual double price() const { return price_; }
private:
	double price_;
};

// Order Stream would be dynamic(online). 
// But for quick implementation, it is static(offline) and data is read from text file
class OrderBook
{
public:

	const double highestPrice()const{}
	const double highestPrice()const{}

	const Order& operator[] (size_t i) const { return *(order_stream_[i]); }
	size_t size() const { return order_stream_.size(); }
	void parse(const char* filename);

	~OrderBook()
	{
		for (size_t i = 0; i < order_stream_.size(); ++i)
		{
			delete order_stream_[i]; order_stream_[i] = NULL; 
		}
	}
private:
	std::deque<const Order*> order_stream_;
};
std::ostream& operator<<(std::ostream& os, const OrderBook& orderstream);


int main(int argc, char ** argv)
{
	if (argc!=2)
	{
		std::cout << "Command need a file name as argument " << std::endl;  return 0;
	}
	
	OrderStream order_stream;
	order_stream.parse(argv[1]) ; //std::cout << order_stream << std::endl;
	
	StreamReader stream_reader;

	stream_reader.processOrderStream(order_stream);

	std::cout << std::endl
		<< " Highest Price " << stream_reader.maxPrice() << std::endl
		<< " Time weighted average price " << stream_reader.timeAveragePrice() << std::endl;

	return 0;
}

void OrderBook::parse(const char* filename)
{
	//std::cout <<" ============= Filename "<< filename << std::endl;
	std::ifstream instream;
	instream.open(filename);

	if (instream.is_open())
	{
		
		while (instream.good())
		{
			std::string line;
			getline(instream, line);
						
			if (line.at(0) != '#') // line start with # is a comment
			{
				//std::cout << line << std::endl;

				std::string cell;
				std::vector<std::string> cell_array;
				std::stringstream line_stream(line);
								
				while (getline(line_stream, cell, ' '))
				{
					cell_array.push_back(cell);
				}
				assert(cell_array.size() < 5);

				const unsigned long time = atoi(cell_array[0].c_str());
				const unsigned orderID = atoi(cell_array[2].c_str());
				if (cell_array.size() == 4)
				{
					assert(cell_array[1].at(0) == 'I');//Insert order
					const double price = atof(cell_array[3].c_str());
					Order* insertOrder = new InsertOrder(time, orderID, price);
					this->push_back(insertOrder);
				}
				else
				{
					assert(cell_array[1].at(0) == 'E' && cell_array.size() == 3);//Insert order
					Order* eraseOrder = new EraseOrder(time, orderID);
					this->push_back(eraseOrder);
				}
				
			}
			else{ std::cout << line << std::endl; }
		}		
	}
	else
	{
		std::cout << filename << " - File not found " << std::endl ; exit(0);
	}

	instream.close();
}

std::ostream& operator<<(std::ostream& os, const Order& order)
{
	if (order.isErease())
		os << order.time << " E " << order.orderID ;
	else
		os << order.time << " I " << order.orderID << " " << order.price() ;
	return os;
}

std::ostream& operator<<(std::ostream& os, const OrderBook& orderstream)
{
	for (size_t i = 0; i < orderstream.size(); ++i)
	{
		std::cout << orderstream[i]<<std::endl;
	}
	return os;
}