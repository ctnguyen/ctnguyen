#include <hello.h>
#include <iostream>

class hello_french : public Base_Hello
{
public:

	void say_hello();

	virtual ~hello_french(){}
};


void hello_french::say_hello()
{
	std::cout << "salut le monde" << std::endl;
}
