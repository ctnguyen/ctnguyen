#ifndef HELLO_ENGLISH_H
#define HELLO_ENGLISH_H

#include <hello.hpp>

class hello_english : public Base_Hello
{
public:

	void say_hello();

	virtual ~hello_english(){}
};

#endif /* HELLO_ENGLISH_H */
