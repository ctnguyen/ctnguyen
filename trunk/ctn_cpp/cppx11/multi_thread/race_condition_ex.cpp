/*! \author chithanhnguyen.math@gmail.com
 *
 *  20.Dec.2014
 *
 *  This is an counter-example of race condition
 *  A class Oscillation is supposed to hold a integer value.
 *
 *  Invariant Condition of the class
 *  Each time that call a oscillate method, this value oscillate, but
 *  always return the state into zero
 *
 *  Two thread without mutex protection will break this invariant.
 *
 */

#include <thread>
#include <iostream>

class Oscillation
{
public:

	Oscillation():m_value(0){}

	void oscillate(const int nb)
	{
		for(int i=0;i<nb;++i) { m_value+=1; }
		for(int i=0;i<nb;++i) { m_value-=1; }
	}

	void print() const { std::cout<< "My Value "<<m_value<<std::endl;}
private:
	int m_value;
};


int main()
{
	Oscillation oscilator;

	std::thread t1(&Oscillation::oscillate, &oscilator, 10000000 );
	std::thread t2(&Oscillation::oscillate, &oscilator, 10000000 );
	t1.join() ;	t2.join();

	oscilator.print();
}
