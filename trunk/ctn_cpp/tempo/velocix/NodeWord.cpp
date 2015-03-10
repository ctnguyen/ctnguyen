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
}


const Word& NodeWord::get_word()       const { return word_;       }
unsigned int NodeWord::get_frequency() const { return frequency_;  }
const NodeWord* NodeWord::get_lnode()  const { return lnode_;      }
const NodeWord* NodeWord::get_rnode()  const { return rnode_;      }

void NodeWord::operator++() 
{
	++frequency_; 
}

void NodeWord::set_lnode(NodeWord* node) 
{
	if (lnode_ != NULL)
		delete lnode_;
	lnode_ = node;
}

void NodeWord::set_rnode(NodeWord* node)
{
	if (rnode_ != NULL)
		delete rnode_;
	rnode_ = node;
}

std::ostream& operator<<(std::ostream &os, const NodeWord& node)
{
	os << "l";
	if (node.get_lnode() != NULL)
	{
		os << node.get_lnode()->get_word();
	}
	else
	{
		os << ".NULL";
	}

	os << "	[" << node. get_frequency() <<"]" << node.get_word() << "	";

	os << "r";
	if (node.get_rnode() != NULL)
	{
		os << node.get_rnode()->get_word();
	}
	else
	{
		os << ".NULL";
	}

	return os;
}