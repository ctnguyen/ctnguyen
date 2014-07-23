#include <iostream>
#include <ctime>
#include <vector>


/*! This small program test how to use timer to generate a seed with good precision
 *  in order of nano secod
 */

void test_UnsignedCounter(unsigned int step);

int main(int, char* []) {

	test_UnsignedCounter( 100000000 );

	return 0;
}


void test_UnsignedCounter(unsigned int step)
{
	unsigned int counter=step+1;

	while(counter >step)
	{
		std::cout<< "Counter "<<counter<<std::endl;	counter+=step;
	}

	std::cout<<std::endl<< "Stopped Counter "<<counter<<std::endl;
}
