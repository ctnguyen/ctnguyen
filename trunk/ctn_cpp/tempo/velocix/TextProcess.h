/*!
 * TextProcess.h
 */
#ifndef TEXTPROCESS_H
#define TEXTPROCESS_H

#include <iostream>

#include "Helper.h"
#include "Word.h"
#include "NodeWord.h"

#define NB_TOP_FREQUENT 3

// the result hold the top frequent node
// by time constraint, the implementation of class Result is very bad
// But the design would allow to modify for the further time
class Result
{
public :
	
	Result();

	void scanR_Node_To_Result(NodeWord* node);

	friend std::ostream& operator<<(std::ostream &os, const Result& res);

private:

	NodeWord* nodes[NB_TOP_FREQUENT];

	// shift element from ith item to the left, i-->i+1
	void shift_left(size_t i); // very bad ctntodo
	bool isFilled() const;
	void push_and_sort(NodeWord* node);
	void exchange_ij(size_t i, size_t j);
};


/*! \class TextProcess
 *  TextProcess add reading word to the container of word and handle
 *  the word's frequency
 */
class TextProcess
{
public :
	TextProcess();
	~TextProcess();

	// throw and exception if not readable
	void read_TextFile(const char* filename); 

	// scan the container and return result
	void get_Result(Result& r) const; // ctntodo move semantic

	// if it is a new word, add to the container
	// if it is a old word, increase the word's frequency
	void add_Word(const Word& word);
	
	friend std::ostream& operator<<(std::ostream &os, const TextProcess& container);

private:

	double reading_file_time_;
	unsigned int nbNode_;

	// DATA Handle the list of world and its frequency
	NodeWord* begin_;
	NodeWord* end_;
	
	// push back modify the end_ pointer
	void push_back(const Word& word);

	// Find if a word already existe in the container, 
	// If yes, return the node, If non, return NULL
	NodeWord* find_Word(const Word& word);

	// recursively print from root
	void printR_NodeWord(std::ostream &os, const NodeWord* rightRootNode) const;

	// recursively delete from root
	void deleteR_NodeWord(NodeWord* rightRootNode);

	// recursively find if a node match the word
	NodeWord* findR_Word(const Word& word, NodeWord* rightRootNode);

	// recursively scan the container and update the result
	void scanR_To_Result(Result& res, NodeWord* rightRootNode) const;
};

#endif /* TEXTPROCESS_H */
