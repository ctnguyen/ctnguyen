/************************************************
 *                                               *
 *   C++ PROGRAMMING                             *
 *   MASTER LAURE ELIE 2013-2014                 *
 *   Student Chi Thanh NGUYEN                    *
 *                                               *
 *   chithanhnguyen.math@gmail.com               *
 *************************************************/

/*!
 *	@file include/header_tp2.hpp
 *	@date 16 Oct 2013
 */


#ifndef M2MO_HEADER_TP2_H
#define M2MO_HEADER_TP2_H

/*! \brief all declaration functions of tp1 will be declared here
 * 
 */
namespace TP2
{

/*! ==  Exercice 2  ==
 *
 * \brief Print adress of a void pointer
 */
void adress(const void *a);


/*! ==  Exercice 3  ==
 *
 * \brief exchange the value of two arguments by givings its pointers
 */
void exchange(int* pa, int*pb);



/*! ==  Exercice 4  ==
 *
 * \brief randomly field of a integer array
 * giving an integer array and its lenght, random_fill will fill randomly all the array by integers numbers
 */
void random_fill(int*const array, const unsigned int array_size);


} // End TP2

#endif /* M2MO_HEADER_TP2_H */
