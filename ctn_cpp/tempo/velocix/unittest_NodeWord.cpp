#define BOOST_TEST_MODULE interview_test_velocix

#include <boost/test/included/unit_test.hpp>

#include "Helper.h"
#include "Word.h"
#include "NodeWord.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(test_NodeWord)

struct NodeWordFixture
{
	NodeWordFixture()
	{
		//lword = new Word();
		std::stringstream lss,rss,css;
		lss << "lText"; rss << "rText";	css << "cText";
		lss >> lword; rss >> rword; css >> cword;
	}
	~NodeWordFixture()
	{		
	}
	Word lword; Word rword; Word cword;
};

BOOST_FIXTURE_TEST_CASE(test_constructor, NodeWordFixture)
{
	NodeWord nodeword(&cword);
	//std::cout << nodeword << std::endl;//ctndebug
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
