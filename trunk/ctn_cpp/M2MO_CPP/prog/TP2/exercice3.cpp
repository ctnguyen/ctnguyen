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
	int a = 1, b = 2;
	std::cout <<"Value before exchange  a=" << a << ", b=" << b ;
	TP2::exchange(&a, &b);
	std::cout <<"     after exchange  a=" << a << ", b=" << b << std::endl;

	return 0;
}
