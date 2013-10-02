#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>

#include <header_tp1.hpp>


namespace TP1
{

// look at http://en.wikipedia.org/wiki/Euclidean_algorithm procedure and implementation (recursion version)
unsigned int pgcd_r(unsigned int a, unsigned int b)
{
	if(a == 0) return b;
	if(b == 0) return a;

	if (a < b)
		return pgcd_r(a,b%a);
	else
		return pgcd_r(b,a%b);
}



int uniform(int a,int b, bool reainitialize_seed)
{
	// http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range

	assert(a<b); //assuming [a,b] formed a non empty interval, then constraint a<b

	// ((double) rand()/ (double) RAND_MAX) give the real uniform distribution in [0,1]
	// Then by linear transform to the interval [a,b], then interger conversion for having the integer distribution

	if(reainitialize_seed)
		srand (time(NULL)); // IMPORTANT reinitialize random seed
	double real_uniform_sample = (double) rand()/ (double) RAND_MAX ;
	int sample = a + (int) (real_uniform_sample * (b - a) );
	return sample;
}




} // end TP1
