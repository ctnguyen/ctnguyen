/*!
 * NodeWord.h
 */
#ifndef NODEWORD_H
#define NODEWORD_H

#include <iostream>

#include "Helper.h"
#include "Word.h"

/*! \class NodeWord
 *  NodeWord is a class implement a node in a linked list
 */
class NodeWord
{
public :
	// the data of a node is a Word and word's frequency
	NodeWord(const Word& word);
	~NodeWord();

	// getters
	const Word& get_word() const;
	unsigned int get_frequency() const;

	// setters
	void operator++();
	void set_lnode(NodeWord* node);
	void set_rnode(NodeWord* node);

	// comparing two node frequence, use for sorting
	bool operator<(const NodeWord& lhs) const;
	bool operator>(const NodeWord& lhs) const;

	friend std::ostream& operator<<(std::ostream &os,const NodeWord& node);

	NodeWord* lnode_;
	NodeWord* rnode_;

private:

	Word word_;
	unsigned int frequency_;	
};

#endif /* NODEWORD_H */
