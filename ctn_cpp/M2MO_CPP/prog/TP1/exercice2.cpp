/************************************************
*                                               *
*   C++ PROGRAMMING                             *
*   MASTER LAURE ELIE 2013-2014                 *
*   Student Chi Thanh NGUYEN                    *
*                                               *
*   chithanhnguyen.math@gmail.com               *
*************************************************/

#include<iostream>
#include <cstdlib>

#include <header_tp1.hpp>


int main(int argc,char* argv[])
{

	int a;int b;

	if (argc != 3) {
		std::cout << "Two arguments expected : excercice1 [a] [b]"<<std::endl;
		return 0;
	}
	else
	{
		a = atoi(argv[1]) ; b = atoi(argv[2]) ;
	}

	unsigned int pgcd = TP1::pgcd_r(a,b);

	std::cout<<std::endl<< "PGCD(" <<a<< ","<< b<<") = "<< pgcd <<std::endl<<std::endl;

	return 0;
}