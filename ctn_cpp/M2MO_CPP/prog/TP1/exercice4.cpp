#include<iostream>
#include <cstdlib>
#include <header_tp1.hpp>


int main(int argc,char* argv[])
{

	unsigned int number;
	std::vector<unsigned int> prime_sequence;

	// reading 1th arguments
	if (argc < 2) {
		std::cout << std::endl<< "Two arguments expected : excercice4 [number_to_decompose]"<<std::endl;
		return 0;
	}
	else
	{
		number = atoi(argv[1]) ;
	}


	TP1::interger_factorrize( prime_sequence, number);
	std::cout<<std::endl<<"Integer Factorization "<<number<<" = ";

	unsigned int seq_size = prime_sequence.size();   // avoiding call vector::size() in the loop

	if(seq_size > 0) std::cout<< prime_sequence[0];  // print the first factor
	for(unsigned int i=1;i< seq_size;++i){           // print the rest of factor sequence
		std::cout<<"*" <<prime_sequence[i];
	}
	std::cout << std::endl<< std::endl;

	return 0;
}
