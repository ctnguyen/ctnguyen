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


#include <header_tp1.hpp>
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
		int sample = TP1::uniform(0,100,false);
		array[i]=sample;
	}
}



// ==  Exercice 5  ==
void vowel_remove(char *const chain)
{
	//predifine explicitly the voyel list
	const unsigned int nb_vowel=12;	char vowel[]="aeiouyAEIOUY";

	//compute chain size;
	unsigned int chain_size=0;
	while(chain[chain_size] != 0) ++chain_size;
	++chain_size;

	unsigned int offset=0;

	// search the vowel from the offset to the end
	// if find vowel, set offset to this position,
	//  - delete the element on position
	//  - shift the queue of the chain
	while(offset<chain_size)
	{
		bool vowel_found = false;

		//check if the element in offset is a vowel
		for(unsigned int i=0;i<nb_vowel;++i)
		{
			if(chain[offset] == vowel[i]) {vowel_found=true ; break;}
		}

		// shift the queue if current character is a vowel, and continu to shift if the current position is a vowel
		unsigned int N_1=chain_size-1;
		while(vowel_found)
		{
			for(unsigned int j=offset;j<N_1;++j)
			{
				char chain_j = chain[j];
				char chain_jj = chain[j+1];
				chain[j]=chain[j+1];
			}

			//resize the character chain
			--chain_size; chain[chain_size]=0;

			//check if the shifted element at offset still is a vowel
			//if yes, pick vowel found to true in order to continu the shift loop
			vowel_found=false;
			for(unsigned int i=0;i<nb_vowel;++i)
			{
				if(chain[offset] == vowel[i]) {vowel_found=true ; break;}
			}
		}

		++offset;
	}
}

























} // end TP2
