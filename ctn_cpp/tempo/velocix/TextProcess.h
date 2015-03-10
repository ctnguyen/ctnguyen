/*!
 * TextProcess.h
 */
#ifndef TEXTPROCESS_H
#define TEXTPROCESS_H

#include <iostream>

#include "Helper.h"
#include "Word.h"
#include "NodeWord.h"

#define NB_TOP_FREQUENT 20

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

	// if it is a new word, add to the container
	// if it is a old word, increase the word's frequency
	void add_Word(const Word& word);
	
	friend std::ostream& operator<<(std::ostream &os, const TextProcess& container);

private:

	double reading_file_time_;
	unsigned int nbNode_;

	// point to top 20 frequent words
	NodeWord* topfrequent_;

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
};

#endif /* TEXTPROCESS_H */
