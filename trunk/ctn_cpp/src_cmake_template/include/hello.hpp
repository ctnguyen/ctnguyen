/************************************************
*     Mini Porject helloworld for cmake         *
*     @authors Chi Thanh NGUYEN                 *
*     contact chithanhnguyen.math@gmail.com     *
*************************************************/
/*!
 *	@file include/hello.h
 *	@date Sept 2013
 */


#ifndef hello_HELLO_H
#define hello_HELLO_H

class Base_Hello
{
public:

	virtual void say_hello() = 0;

	virtual ~Base_Hello(){}
};

#endif /* hello_HELLO_H */
