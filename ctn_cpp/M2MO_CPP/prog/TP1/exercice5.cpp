/************************************************
*                                               *
*   C++ PROGRAMMING                             *
*   MASTER LAURE ELIE 2013-2014                 *
*   Student Chi Thanh NGUYEN                    *
*                                               *
*   chithanhnguyen.math@gmail.com               *
*************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>

#include<header_tp1.hpp>

int main(int argc,char* argv[])
{
	unsigned int i_number; unsigned int i_sqrt;
	double r_number;double r_sqrt;
	double eps=1e-4;

	// reading 1th arguments
	if (argc < 2) {
		std::cout << std::endl<< "At least one arguments expected : excercice5 [number]"<<std::endl;
		std::cout << "If the argument has a point, it is considered as a real number"<<std::endl;
		return 0;
	}


	char *is_real_number = strchr(argv[1],'.');
	if(is_real_number == NULL) 	i_number = atoi(argv[1]);
	else r_number = atof(argv[1]);

	if (argc > 2) eps = atof(argv[2]);


	if(is_real_number == NULL)
	{
		i_sqrt = TP1::integer_sqrt(i_number);
		std::cout << "Integer part of Square root of "<<i_number<<" is "<<i_sqrt <<std::endl<<std::endl;
	}
	else
	{
		r_sqrt = TP1::newton_sqrt(r_number,eps);
		std::cout << "Square root of "<<r_number<<" is "<<r_sqrt <<" finding with eps="<<eps <<std::endl
				  << "Test by remultiplicate  :  "<<  r_sqrt<<"*"<<r_sqrt<<" = "<< r_sqrt*r_sqrt<<std::endl<<std::endl;
	}

	return 0;
}
