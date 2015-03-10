/*!
 * Word.h
 */
#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <fstream>

#include "Helper.h"

/*! \class Word
 *  Word is a class used for handling ifstream
 */
class Word
{
public:

	Word();
	~Word();

	// check if word is empty
	bool empty() const;

	// get the text of the word
	const char* get_text() const ;

	// i\o operator
	friend std::ostream& operator<<(std::ostream &os, const Word& word);
	friend std::istream& operator>>(std::istream &is, Word& bignum);

private :
	// the text of the word
	char* text_;

	// check if a character is a symbol or a blank
	bool is_Symbol(const char& c) const ;
};

#endif /* WORD_H */
