/************************************************
*     Mini Porject helloworld for cmake         *
*     @authors Chi Thanh NGUYEN                 *
*     contact chithanhnguyen.math@gmail.com     *
*************************************************/
/*!
 *	@file include/moduels/hello_vietnamese.hpp
 *	@date Sept 2013
 */


#ifndef HELLO_VIETNAMESE_H
#define HELLO_VIETNAMESE_H

#include <hello.hpp>

class hello_vietnamese : public Base_Hello
{
public:

	void say_hello();

	virtual ~hello_vietnamese(){}
};

#endif /* HELLO_VIETNAMESE_H */
