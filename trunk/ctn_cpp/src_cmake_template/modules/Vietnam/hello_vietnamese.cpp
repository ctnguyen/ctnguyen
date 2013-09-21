#include <hello.h>
#include <iostream>

class hello_vietnamese : public Base_Hello
{
public:

	void say_hello();

	virtual ~hello_vietnamese(){}
};


void hello_vietnamese::say_hello()
{
	std::cout << "Xin chao the gioi" << std::endl;
}
