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
	// the data of a node is a Word
	NodeWord(Word* word);
	~NodeWord();

	// getters
	const Word* get_word() const;
	unsigned int get_frequency() const;
	
	const NodeWord* get_lnode() const;
	const NodeWord* get_rnode() const;

	// setters
	void operator++();
	void set_lnode(NodeWord* node);
	void set_rnode(NodeWord* node);

	friend std::ostream& operator<<(std::ostream &os, const NodeWord& node);
private:

	unsigned int frequency_;
	Word* word_;
	
	NodeWord* lnode_;
	NodeWord* rnode_;
};

#endif /* NODEWORD_H */
