/************************************************
*                                               *
*   C++ PROGRAMMING                             *
*   MASTER LAURE ELIE 2013-2014                 *
*   Student Chi Thanh NGUYEN                    *
*                                               *
*   chithanhnguyen.math@gmail.com               *
*************************************************/

#include <iostream>

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





} // end TP2
