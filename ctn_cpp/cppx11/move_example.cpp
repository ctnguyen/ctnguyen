/*! \author chithanhnguyen.math@gmail.com
 *
 *  21.Dec.2014
 *
 *  a set of example to understand lvalue, rvalue (temporary),
 *  move semantics
 *
 */

#include <iostream>
 
class Toto
{
public:

	// Rule of Five
	Toto(const int x):m_value(x) { log("  Valued Constructor"); }
	Toto():m_value(0) { log("  Default Constructor"); }
	Toto(const Toto& toto) { log("  Copy Constructor"); }
	Toto(Toto&& toto) { log("  MOVE Constructor"); }

	Toto& operator=(const Toto& toto) {	log("  Copy assignment operator"); return *this; }

	Toto& operator=(const Toto&& toto)
	{
		log("  MOVE Copy assignment operator");
		m_value=toto.m_value;
		return *this;
	}

	~Toto() { log("  Destructor"); }

	// Temporary Operators
	Toto operator+(const Toto& rhs)
	{
		log("  Creation Temporary");
		std::cout<<"      + add operator ["<<this<<"."<<this->m_value<<"+"<<&rhs<<"."<<rhs.m_value<<"]" <<std::endl;
		Toto temporary(this->m_value + rhs.m_value);
		return temporary;
	}

private:
	void log(const char* msg)
	{
		std::cout<<msg<<" from ["<<this<<"("<<m_value<< ")]"<<std::endl;
	}

	int m_value;
};

int main(int argc, char **argv)
{
	Toto a(1);
	Toto b(2);
	Toto c(30);

	//std::cout<<std::endl<<"Start Assignment operator"<<std::endl;
	//b=a;
	//std::cout<<"End Assignment operator"<<std::endl;

	std::cout<<std::endl<<"Start MOVE Assignment operator"<<std::endl;
	//Toto& non_const_ref_toto = a+b  ; // temporary bind to a nonconst ref is illegal
	const Toto& cons_ref_toto = a+b ; // temporary bind to a const ref is legal
	//c=a+b;                            // temporary bind to a lvalue is legal
	std::cout<<"End MOVE Assignment operator"<<std::endl;
	return 0;
}
