/*!
 *	@file include/header_TP1.hpp
 *	@date Sept 2013
 */
#include <vector>


#ifndef M2MO_HEADER_TP1_H
#define M2MO_HEADER_TP1_H

/*! \brief all declaration functions of tp1 will be declared here
 * 
 */
namespace TP1
{

/*! Exercice 2
 * Function returning the Greatest Common Divisor (pgcd in French) using recursive algorithm
 * [1] http://en.wikipedia.org/wiki/Euclidean_algorithm
 */
unsigned int pgcd_r(unsigned int a, unsigned int b);


/*! Exercice 3
 *  Uniform Random Generator : generate random integer between given a and b
 *  For trivial implementation, one can use [1], for advanced algorithm (take times), use [2]
 *  [1] http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
 *  [2] http://en.wikipedia.org/wiki/Rejection_sampling
 *  [3] http://stackoverflow.com/questions/137783/expand-a-random-range-from-15-to-17
 */
int uniform(int a,int b, bool reainitialize_seed=true);



/*! Exercice 4
 *  Interger Factorization We use the simplest method [2] for this exercice
 *
 *  [1] http://en.wikipedia.org/wiki/Integer_factorization
 *  [2] http://en.wikipedia.org/wiki/Trial_division
 */
void interger_factorrize(std::vector<unsigned int> & prime_sequence, unsigned int number);



} // End TP1

#endif /* M2MO_HEADER_TP1_H */
