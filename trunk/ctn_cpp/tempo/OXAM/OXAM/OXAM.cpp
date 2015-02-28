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
	Order(unsigned long _time = 0, unsigned int _orderID = 0) :time(_time), orderID(_orderID){}
	unsigned long time;
	unsigned orderID;
	virtual bool isErease() const = 0 ;
	virtual bool isInsert() const = 0;
	virtual double price() const = 0;

	bool operator ==(const Order& l) const { return ( orderID == l.orderID ); }
};
std::ostream& operator<<(std::ostream& os, const Order& order);

class EraseOrder : public Order
{
public:
	EraseOrder(unsigned long _time = 0, unsigned int _orderID = 0) :Order(_time, _orderID){}
	virtual bool isErease() const { return true; };
	virtual bool isInsert() const { return false; };
	virtual double price() const { throw("EreaseOrder do not have price"); return -100000; }
};

class InsertOrder : public Order
{
public:
	InsertOrder(unsigned long _time = 0, unsigned int _orderID = 0, const double& _price = 0)
	: Order(_time, _orderID), price_(_price){}
	
	virtual bool isErease() const { return false ; }
	virtual bool isInsert() const { return true  ; }
	virtual double price() const { return price_; }

	InsertOrder(const InsertOrder& rhs)
	: Order(rhs.time, rhs.orderID), price_(rhs.price() ) {}

	InsertOrder& operator=(const InsertOrder& rhs)
	{
		time = rhs.time; orderID = rhs.orderID; price_ = rhs.price_;
		return *this; 
	}
private:
	double price_;
};

// InputOrderContainer would be dynamic(online). 
// But for quick implementation, it is static(offline) and data is read from text file
// InputOrderContainer's data should also be simulated for test
class InputOrderContainer
{
public:

	double highestPrice()const; 

	const Order& operator[] (size_t i) const { return *(order_stream_[i]); }
	
	size_t size() const { return order_stream_.size(); }
	
	void parse(const char* filename);

	//ctntodo (Only run for test) Method checking if the order book satisfied all conditions
	bool check_goodness_order_book(){ return true; }

	~InputOrderContainer()
	{
		for (size_t i = 0; i < order_stream_.size(); ++i)
		{
			delete order_stream_[i]; order_stream_[i] = NULL; 
		}
	}
private:
	std::vector<const Order*> order_stream_;
};
std::ostream& operator<<(std::ostream& os, const InputOrderContainer& orderstream);

class OrderBook
{
public:
	
	double highestPrice()const;
		
	double time_weighted_average() const;
	
	void erase(unsigned long erased_time, const unsigned int orderID);
	void insert(unsigned long inserted_time, unsigned int orderID, const double& price);

	friend std::ostream& operator<<(std::ostream& os, const OrderBook& orderbook);
private:
	
	std::map<unsigned int, InsertOrder> m_order_book_;
	
	double time_average_buffer;
	double highest_price_buffer;
	double total_time_buffer;
};




int main(int argc, char ** argv)
{
	if (argc!=2)
	{
		std::cout << "Command need a file name as argument " << std::endl;  return 0;
	}
	
	InputOrderContainer order_stream;
	order_stream.parse(argv[1]); std::cout << order_stream << std::endl << std::endl;
	
	OrderBook order_book;
	for (size_t i = 0; i < order_stream.size(); ++i)
	{
		const Order& order = order_stream[i];
		if (order.isInsert())
			order_book.insert(order.time,order.orderID,order.price());
		else//is erase order
			order_book.erase(order.time,order.orderID);

		std::cout << "Highest Price=" << order_book.highestPrice()
			<< "Time_Price Average=" << order_book.time_weighted_average() << std::endl
			<< order_book << std::endl << std::endl;
	}
	/*
	StreamReader stream_reader;

	stream_reader.processOrderStream(order_stream);

	std::cout << std::endl
		<< " Highest Price " << stream_reader.maxPrice() << std::endl
		<< " Time weighted average price " << stream_reader.timeAveragePrice() << std::endl;
	*/
	return 0;
}


double OrderBook::highestPrice()const
{
	if (m_order_book_.empty())
		return std::numeric_limits<double>::quiet_NaN();
	else
		return highest_price_buffer;
}

double OrderBook::time_weighted_average() const
{
	if (m_order_book_.empty())
		return std::numeric_limits<double>::quiet_NaN();
	else
		return time_average_buffer;
}

void OrderBook::erase(unsigned long erased_time, unsigned int orderID)
{
	assert(!m_order_book_.empty());
	assert( erased_time > m_order_book_[orderID].time);
	
	const unsigned int order_duration = erased_time - m_order_book_[orderID].time;
	const double order_price = m_order_book_[orderID].price();
	
	m_order_book_.erase(orderID);
	
	const double& old_total_time = total_time_buffer;
	
	// update time average price for all order
	time_average_buffer *= old_total_time;
	time_average_buffer += order_duration*order_price;

	//update total time
	total_time_buffer += order_duration;
	time_average_buffer /= time_average_buffer;

}
void OrderBook::insert(unsigned long inserted_time, unsigned int orderID, const double& price)
{
	InsertOrder new_inserted_order(inserted_time, orderID, price);
	m_order_book_[orderID] = new_inserted_order;

	if (highest_price_buffer < price) highest_price_buffer = price;
}


double InputOrderContainer::highestPrice()const
{
	double highest_price = 0;


	return highest_price;
}

void InputOrderContainer::parse(const char* filename)
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
					order_stream_.push_back(insertOrder);
				}
				else
				{
					assert(cell_array[1].at(0) == 'E' && cell_array.size() == 3);//Insert order
					Order* eraseOrder = new EraseOrder(time, orderID);
					order_stream_.push_back(eraseOrder);
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

std::ostream& operator<<(std::ostream& os, const InputOrderContainer& orderstream)
{
	for (size_t i = 0; i < orderstream.size(); ++i)
	{
		std::cout << orderstream[i]<<std::endl;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const OrderBook& orderbook)
{
	std::map<unsigned int, InsertOrder>::const_iterator it = orderbook.m_order_book_.begin();
	while (it != orderbook.m_order_book_.end())
	{
		const Order& order = it->second;
		std::cout << order << std::endl;
		++it;
	}
	return os;
}