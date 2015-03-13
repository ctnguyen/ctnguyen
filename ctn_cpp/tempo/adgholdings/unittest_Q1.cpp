#define BOOST_TEST_MODULE interview_test_adgholdings

#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <fstream>

#include "Question1.h"
BOOST_AUTO_TEST_SUITE(test_Question1)

BOOST_AUTO_TEST_CASE(test_constructor)
{
	Q1::Character mchar_a('a');
	//std::cout << mchar_a << std::endl;//ctndebug
	++mchar_a;
	//std::cout << mchar_a << std::endl;//ctndebug
	
	Q1::Character mchar_b('B');
	//std::cout << mchar_b << std::endl;//ctndebug
	
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_comparing_operator)
{
	Q1::Character chara('a');
	Q1::Character charaa('a');
	Q1::Character charb('b');
	Q1::Character charz('z');
	BOOST_CHECK(!(chara < charaa));
	BOOST_CHECK(chara < charb);
	BOOST_CHECK(chara < charz);
	BOOST_CHECK(charb < charz);
}

BOOST_AUTO_TEST_CASE(test_function_q2)
{
	std::list<char> res;

	Q1::GetMostUsedCharacters("annoying", res);
	Q1::printList(res);

	Q1::GetMostUsedCharacters("implementation", res);
	Q1::printList(res);

}


BOOST_AUTO_TEST_SUITE_END()
