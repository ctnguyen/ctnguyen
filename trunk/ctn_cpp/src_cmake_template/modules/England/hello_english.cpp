#include <hello.h>
#include <iostream>

class hello_english : public Base_Hello
{
public:

	void say_hello();

	virtual ~hello_english(){}
};


void hello_english::say_hello()
{
	std::cout << "hello world" << std::endl;
}
