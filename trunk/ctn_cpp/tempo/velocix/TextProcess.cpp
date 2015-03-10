#include "TextProcess.h"

#include <cassert>


TextProcess::TextProcess()
: reading_file_time_(-100000.)// initiate to absurd value
, nbNode_(0)
, begin_(NULL)
, end_(NULL)
{
}

TextProcess::~TextProcess()
{
	deleteR_NodeWord(begin_);
	begin_ = NULL; end_ = NULL; 
}

void TextProcess::read_TextFile(const char* filename)
{
	throw("TextProcess::read_TextFile not implemented");
}

void TextProcess::get_Result(Result& r) const
{
	

}

void TextProcess::add_Word(const Word& word)
{
	assert( !word.empty() );

	NodeWord* node = find_Word(word);
	if (node == NULL)
	{
		push_back(word);
	}
	else
	{
		++(*node);
	}	
}

void TextProcess::push_back(const Word& word)
{
	if (end_ != NULL)	assert(end_->lnode_ == NULL);
	NodeWord* newNode = new NodeWord(word);
	
	if (begin_ != NULL) // if linked list is not empty
	{
		newNode->set_rnode(end_);
		if (end_ != NULL) end_->set_lnode(newNode);
		end_ = newNode;
	}
	else
	{
		begin_ = newNode;
		end_ = newNode;
	}
	++nbNode_;
}

NodeWord* TextProcess::find_Word(const Word& word)
{
	return findR_Word(word, begin_);
}

std::ostream& operator<<(std::ostream &os, const TextProcess& container)
{
	if (container.begin_ != NULL)
	{		
		container.printR_NodeWord(os, container.begin_);
		std::cout << std::endl << " ---  Number of NodeWord = " << container.nbNode_ << std::endl;
	}
	else
	{
		os << "TextProcess is empty";
	}

	return os;
}

void TextProcess::printR_NodeWord(std::ostream &os, const NodeWord* rightRootNode) const
{
	if (rightRootNode!=NULL)
		os << "[" << rightRootNode->get_frequency()<<"] "<< rightRootNode->get_word() << std::endl;

	if (rightRootNode->lnode_ != NULL)
		printR_NodeWord(os, rightRootNode->lnode_);
}

void TextProcess::deleteR_NodeWord(NodeWord* rightRootNode)
{
	NodeWord* lnode=NULL;
	if (rightRootNode != NULL)
	{
		lnode = rightRootNode->lnode_;
		delete rightRootNode; rightRootNode = NULL;
	}

	if (lnode!=NULL)
	{
		deleteR_NodeWord(lnode);
	}
}

NodeWord* TextProcess::findR_Word(const Word& word, NodeWord* rightRootNode)
{
	if (rightRootNode == NULL) return NULL;

	if (rightRootNode->get_word() == word) return rightRootNode;

	findR_Word(word, rightRootNode->lnode_);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const Result& res)
{
	os << "Hello, I am result";
	return os;
}
