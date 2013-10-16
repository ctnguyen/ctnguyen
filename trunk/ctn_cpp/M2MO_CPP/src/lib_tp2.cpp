/************************************************
*                                               *
*   C++ PROGRAMMING                             *
*   MASTER LAURE ELIE 2013-2014                 *
*   Student Chi Thanh NGUYEN                    *
*                                               *
*   chithanhnguyen.math@gmail.com               *
*************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>


#include <header_tp2.hpp>


namespace TP2
{

//==  Exercice 2  ==
void adress(const void *a)
{
	std::cout<<"hello adress void pointer "<< a <<std::endl;
}


// ==  Exercice 3  ==
void exchange(int* pa, int*pb)
{
	const int tempo = *pa ;
	*pa = *pb ;
	*pb = tempo;
}



// ==  Exercice 4  ==
void random_fill(int *const array, const unsigned int array_size)
{
	srand (time(NULL)); // IMPORTANT reinitialize random seed

	for(unsigned int i=0;i<array_size;++i)
	{
		int sample = rand();
		array[i]=sample;
	}
}





} // end TP2
