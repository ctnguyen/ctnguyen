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
#include <cassert>
#include <ctime>
#include <algorithm>
#include <cmath>

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



void interger_factorrize(std::vector<unsigned int> & result, unsigned int N)
{
	// clear the vector of result before puting the prime sequence factorized in it
	result.clear();

	// We use the trial division algorithm for the factorisation
	// Running a "candidate" divisor increasing sequence
	// Test if candidate divide the number
	// If yes, save the candidate, reset the number to the quotient, relaunch the loop
	// If non, increment candidate
	// When candidate > number, stop loop and put the nunber lastly to the sequence of factors

	unsigned int candidate=2;
	unsigned int number =N;

	while( candidate < number )
	{
		// While the candidate divide the number, do two things
		while(number%candidate == 0)
		{
			// this candidate is good then store it to the result sequence
			result.push_back(candidate);
			// now only the quotient part need to be factorize
			number/=candidate;
		}
		++candidate;
	}

	//sort the result in the decreasing order
	std::sort(result.begin(), result.end());
}



unsigned int integer_sqrt(unsigned int N)
{
	if ( N <2 ) return N;
	unsigned int int_sqrt = 1;

	while ( int_sqrt*int_sqrt <= N) ++int_sqrt;

	--int_sqrt;// decrement for its square be smaller than N

	return int_sqrt;
}

double newton_sqrt(const double &S, const double &epsilon)
{
	// see [1] for notation and method
	// for the newton method, we choose roughly the initial point as the mid of S
	// remark : when S is close to zero, the newton method does not work well
	//          because its derivative is near zero, dividing by this give a very big value

	double x_n  = 0.5*S; //initiate the point x_n
	double x_nn =     S; //initiate the point x_{n+1}
	double x_buffer = x_nn ;

	while( abs(x_nn*x_nn - x_n*x_n) >epsilon )
	{
		x_buffer = x_nn ;           // reserve the value of
		x_nn = 0.5 * (x_n + S/x_n); // advance one step for the iteration
		x_n = x_buffer ;            // set x_n to the older value of precedent step
	}

	return x_n;
}


} // end TP1
