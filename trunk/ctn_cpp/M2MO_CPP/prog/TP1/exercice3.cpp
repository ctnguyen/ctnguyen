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
#include <ctime>
#include <header_tp1.hpp>


int main(int argc,char* argv[])
{

	int a;int b;

	// reading 1th and 2th arguments
	if (argc < 3) {
		std::cout << "Two arguments expected : excercice1 [min_bound] [max_bound]"<<std::endl;
		return 0;
	}
	else
	{
		a = atoi(argv[1]) ; b = atoi(argv[2]) ;
	}


	if(argc == 3)
	{
		// if programme have only two arguments, then generate the uniform integer dist in [a,b]
		std::cout<<std::endl<< "Uniform Random Generator between " <<a<< " and "<< b<<" : "<< TP1::uniform(a,b) <<std::endl<<std::endl;
	}
	else
	{
		// if programme has 3-th argument, test regularity of sample with the nb_sample = 3-th argument
		unsigned int nb_sample = atoi(argv[3]);
		srand (time(NULL)); // IMPORTANT reinitialize random seed
		for(unsigned int i=0;i<nb_sample;++i)
			std::cout<< i <<"-th URG between " <<a<< " and "<< b<<" : "<< TP1::uniform(a,b,false) <<std::endl;
	}

	return 0;
}
