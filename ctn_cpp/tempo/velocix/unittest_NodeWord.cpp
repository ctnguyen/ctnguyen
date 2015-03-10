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
	NodeWord nodeword(cword);
	BOOST_CHECK(nodeword.get_frequency() == 1);
	//std::cout << nodeword << std::endl;//ctndebug
	++nodeword;
	BOOST_CHECK(nodeword.get_frequency() == 2);
	//std::cout << nodeword << std::endl;//ctndebug

	BOOST_CHECK(true);
}

BOOST_FIXTURE_TEST_CASE(test_set_link, NodeWordFixture)
{
	NodeWord cnode(cword);
	NodeWord* lnode = new NodeWord(lword);
	NodeWord* rnode = new NodeWord(rword);
	
	BOOST_CHECK(cnode.lnode_ == NULL);
	BOOST_CHECK(cnode.rnode_ == NULL);
	//std::cout << cnode << std::endl;//ctndebug

	cnode.set_lnode(lnode);
	cnode.set_rnode(rnode);

	BOOST_CHECK(cnode.lnode_ != NULL);
	BOOST_CHECK(cnode.rnode_ != NULL);
	//std::cout << cnode << std::endl;//ctndebug

	delete lnode;
	delete rnode;
}

BOOST_FIXTURE_TEST_CASE(test_comparator, NodeWordFixture)
{
	NodeWord node1(cword);
	NodeWord node2(rword);
	NodeWord node3(lword);

	++node2;
	++node3; ++node3;

	BOOST_CHECK(node1<node2);
	BOOST_CHECK(node2<node3);
	BOOST_CHECK(node3>node1);
	
}


BOOST_AUTO_TEST_SUITE_END()
