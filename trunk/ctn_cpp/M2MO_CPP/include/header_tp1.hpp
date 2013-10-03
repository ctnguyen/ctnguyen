/************************************************
 *                                               *
 *   C++ PROGRAMMING                             *
 *   MASTER LAURE ELIE 2013-2014                 *
 *   Student Chi Thanh NGUYEN                    *
 *                                               *
 *   chithanhnguyen.math@gmail.com               *
 *************************************************/

/*!
 *	@file include/header_tp1.hpp
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

/*! ==  Exercice 2  ==
 *
 * Function returning the Greatest Common Divisor (pgcd in French) using recursive algorithm
 * [1] http://en.wikipedia.org/wiki/Euclidean_algorithm
 */
unsigned int pgcd_r(unsigned int a, unsigned int b);


/*! ==  Exercice 3  ==
 *
 *  Uniform Random Generator : generate random integer between given a and b
 *  For trivial implementation, one can use [1], for advanced algorithm (take times), use [2]
 *  [1] http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
 *  [2] http://en.wikipedia.org/wiki/Rejection_sampling
 *  [3] http://stackoverflow.com/questions/137783/expand-a-random-range-from-15-to-17
 */
int uniform(int a,int b, bool reainitialize_seed=true);



/*! ==  Exercice 4  ==
 *
 *  Interger Factorization We use the simplest method [2] for this exercice
 *  [1] http://en.wikipedia.org/wiki/Integer_factorization
 *  [2] http://en.wikipedia.org/wiki/Trial_division
 */
void interger_factorrize(std::vector<unsigned int> & prime_sequence, unsigned int number);




/*! ==  Exercice 5  ==
 *
 *  Manually Computing Square Root
 *  [1] http://en.wikipedia.org/wiki/Methods_of_computing_square_roots
 */

// Function returning the integer part of a integer number's square root
unsigned int integer_sqrt(unsigned int N);

// Function returning the approximation square root of a real number, with tolerance epsilon
double newton_sqrt(const double &r, const double &epsilon);




/*! ==  Exercice 6  ==
 */
class Point
{
public:

	///! The ONLY Constructor
	Point(int ab, int ord, char name);

	///! translate the point to (x,y)
	void translate(int x, int y);

	///! printout the point'name, and its coordinates
	void affiche() const;

	///! destructor
	~Point();

private:

	char nom;     // name of point
	int abscisse; // abscisse of point
	int ordonne;  // ordonne of point
};


} // End TP1

#endif /* M2MO_HEADER_TP1_H */
