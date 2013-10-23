/************************************************
*                                               *
*   C++ PROGRAMMING                             *
*   MASTER LAURE ELIE 2013-2014                 *
*   Student Chi Thanh NGUYEN                    *
*                                               *
*   chithanhnguyen.math@gmail.com               *
*************************************************/

#include<iostream>

#include<header_tp2.hpp>

using namespace std;


int main(int /*argc*/,char** /*argv*/)
{
	char chain[] = "Master Laure Elie Molelisation Aleatoire";

	std::cout<<"Chaine before truncating vowel \""<<chain<<"\""<<std::endl;
	TP2::vowel_remove(chain);
	std::cout<<"Chaine  after truncating vowel \""<<chain<<"\""<<std::endl;

	return 0;
}
