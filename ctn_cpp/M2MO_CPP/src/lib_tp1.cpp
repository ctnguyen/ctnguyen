#include <iostream>
#include <header_tp1.hpp>


namespace TP1
{

// look at http://en.wikipedia.org/wiki/Euclidean_algorithm
// procedure and implementation (recursion version)
unsigned int pgcd_r(unsigned int a, unsigned int b)
{
	if(a == 0) return b;
	if(b == 0) return a;

	if (a < b)
		return pgcd_r(a,b%a);
	else
		return pgcd_r(b,a%b);
}




} // end TP1
