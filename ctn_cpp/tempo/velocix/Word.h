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
	Word(const Word&);
	Word& operator=(const Word&);
	~Word();

	// check if word is empty, to use before every use of Word, except the >> operator
	bool empty() const;

	// get the text of the word
	const char* get_text() const ;

	// comparing two words
	bool operator==(const Word& lhs) const;
	bool operator!=(const Word& lhs) const;

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
