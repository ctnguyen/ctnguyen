#include "NodeWord.h"
#include <cassert>

NodeWord::NodeWord(const Word& word)
: frequency_(1)
, word_(word)
, lnode_(NULL)
, rnode_(NULL)
{
	// word passed to node can not be empty
	assert(!word_.empty());
}

NodeWord::~NodeWord()
{
	lnode_ = NULL; rnode_ = NULL;
}


const Word& NodeWord::get_word()       const { return word_;       }
unsigned int NodeWord::get_frequency() const { return frequency_;  }

void NodeWord::operator++() 
{
	++frequency_; 
}

void NodeWord::set_lnode(NodeWord* node) 
{
	if (lnode_ != NULL)
	{
		std::cout << "ATTENTION : a left node was deleted to be reset" << std::endl;
		delete lnode_;
	}
	lnode_ = node;
}

void NodeWord::set_rnode(NodeWord* node)
{
	if (rnode_ != NULL)
	{
		std::cout << "ATTENTION : a right node was deleted to be reset" << std::endl;
		delete rnode_;
	}
	rnode_ = node;
}

std::ostream& operator<<(std::ostream &os, const NodeWord& node)
{
	os << "l";
	if (node.lnode_ != NULL)
	{
		os << node.lnode_->get_word();
	}
	else
	{
		os << ".NULL";
	}

	os << "	[" << node. get_frequency() <<"]" << node.get_word() << "	";

	os << "r";
	if (node.rnode_ != NULL)
	{
		os << node.lnode_->get_word();
	}
	else
	{
		os << ".NULL";
	}

	return os;
}