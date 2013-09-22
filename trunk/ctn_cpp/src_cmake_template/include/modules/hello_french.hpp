#ifndef HELLO_FRENCH_H
#define HELLO_FRENCH_H

#include <hello.hpp>

class hello_french : public Base_Hello
{
public:

	void say_hello();

	virtual ~hello_french(){}
};

#endif /* HELLO_FRENCH_H */
