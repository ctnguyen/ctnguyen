// http://stackoverflow.com/questions/11110604/why-is-boosts-matrix-multiplication-slower-than-mine

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/operation_blocked.hpp>
#include <ctime>

#include <test/testlib/Test.h>

using namespace boost::numeric::ublas;

void test_BoostUBLASMatrix()
{
	std::cout << "begin the calculation of matrix multiplication" << std::endl;
	size_t z1 = 1000;
	size_t z2 = z1;
	boost::numeric::ublas::matrix<double> m1(z1,z2);
	for(size_t i=0; i<m1.size1(); ++i)
		for(size_t j=0; j<m1.size1(); ++j)
			m1(i,j) = i*10+j;

   
	boost::numeric::ublas::matrix<double> m2(z1,z2);
	for(size_t i=0; i<m1.size1(); ++i)
	{
		for(size_t j=0; j<m1.size1(); ++j)
		{
			m1(i,j) = i+j*10;
			std::cout<<"Mat["<<i<<","<<j<<"]"<<std::endl;
		}
	}


	clock_t t1,t2;
	double diff;
	boost::numeric::ublas::matrix<double> m;

	t1 = clock();
	m = boost::numeric::ublas::prod(m1,m2);
	t2 = clock();
	diff = t2 - t1;
	std::cout << "prod use time = " << diff << std::endl;

	t1 = clock();
	m = block_prod<matrix<double>,1024>(m1,m2); 
	t2 = clock();
	diff = t2 - t1;
	std::cout << "block_prod use time = " << diff << std::endl;
}