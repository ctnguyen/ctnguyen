/************************************************
*                                               *
*   C++ PROGRAMMING                             *
*   MASTER LAURE ELIE 2013-2014                 *
*   Student Chi Thanh NGUYEN                    *
*                                               *
*   chithanhnguyen.math@gmail.com               *
*************************************************/

#include<iostream>
#include<cstdlib>

#include<header_tp2.hpp>

using namespace std;


int main(int argc,char** argv)
{
	const unsigned int array_size = 20;
	int int_array[array_size];
	TP2::random_fill(int_array,array_size);

	std::cout<< std::endl<< "generated array ";
	for(unsigned int i=0;i<array_size;i++)
		std::cout<< int_array[i]<<" ";
	std::cout<< std::endl<< std::endl;
	return 0;
}
