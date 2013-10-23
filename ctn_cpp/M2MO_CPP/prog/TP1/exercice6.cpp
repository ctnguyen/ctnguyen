/************************************************
*                                               *
*   C++ PROGRAMMING                             *
*   MASTER LAURE ELIE 2013-2014                 *
*   Student Chi Thanh NGUYEN                    *
*                                               *
*   chithanhnguyen.math@gmail.com               *
*************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>

#include<header_tp1.hpp>

int main(int /*argc*/,char** /*argv*/)
{
	TP1::Point m_point(1,3,'A');
	m_point.affiche();
	m_point.translate(3,7);
	m_point.affiche();

	return 0;
}
