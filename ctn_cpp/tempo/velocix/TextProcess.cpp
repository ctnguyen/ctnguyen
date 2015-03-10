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
	assert(begin_ != NULL);
	scanR_To_Result(r, begin_);
}

void TextProcess::add_Word(const Word& word)
{
	assert(!word.empty());

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
	if (rightRootNode != NULL)
		os << "[" << rightRootNode->get_frequency() << "] " << rightRootNode->get_word() << std::endl;

	if (rightRootNode->lnode_ != NULL)
		printR_NodeWord(os, rightRootNode->lnode_);
}

void TextProcess::deleteR_NodeWord(NodeWord* rightRootNode)
{
	NodeWord* lnode = NULL;
	if (rightRootNode != NULL)
	{
		lnode = rightRootNode->lnode_;
		delete rightRootNode; rightRootNode = NULL;
	}

	if (lnode != NULL)
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

void TextProcess::scanR_To_Result(Result& res, NodeWord* rightRootNode) const
{
	if (rightRootNode != NULL)
	{
		res.scanR_Node_To_Result(rightRootNode);

		if (rightRootNode->lnode_ != NULL)
		{
			scanR_To_Result(res, rightRootNode->lnode_);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


Result::Result()
{
	for (size_t i = 0; i < NB_TOP_FREQUENT; ++i)
	{
		nodes[i] = NULL;
	}
}

void Result::shift_left(size_t I)
{
	assert(I < NB_TOP_FREQUENT);
	for (size_t ii = NB_TOP_FREQUENT - 1; ii > I; --ii)
	{
		size_t i = ii - 1;
		nodes[ii] = nodes[i];
	}
}

bool Result::isFilled() const
{
	return (nodes[NB_TOP_FREQUENT - 1] != NULL);
}

void Result::push_and_sort(NodeWord* node)
{
	assert(!isFilled());
	
	// find the first NULL item in result
	size_t I = 0;
	while (I < NB_TOP_FREQUENT && nodes[I] != NULL) ++I;
	nodes[I] = node;

	// sort (a bad algorightm)
	for (size_t i = 0; i < I; ++i)
	{
		NodeWord& node_i = *nodes[i];
		for (size_t j = i+1; j <= I; ++j)
		{
			NodeWord& node_j = *nodes[j];
			if (node_j > node_i)
			{
				exchange_ij(i, j);
			}
		}
	}
}

void Result::exchange_ij(size_t i, size_t j)
{
	NodeWord* node_i = nodes[i];
	nodes[i] = nodes[j];
	nodes[j] = node_i;
}

void Result::scanR_Node_To_Result(NodeWord* node)
{
	if (isFilled())
	{
		const NodeWord& node_to_insert = *node;

		size_t ii = NB_TOP_FREQUENT;

		while (ii > 0)
		{
			size_t i = ii - 1;

			const NodeWord& node_i = *nodes[i];
			if (node_to_insert < node_i) break;
			
			--ii;
		}

		if (ii < NB_TOP_FREQUENT)
		{
			shift_left(ii);
			nodes[ii] = node;
		}
	}
	else
	{
		push_and_sort(node);
	}
}

std::ostream& operator<<(std::ostream &os, const Result& res)
{
	for (size_t i = 0; i < NB_TOP_FREQUENT; ++i)
	{
		assert(res.nodes[i] != NULL);
		os << "[" << res.nodes[i]->get_frequency() << "] " << res.nodes[i]->get_word() << std::endl;
	}
	return os;
}
