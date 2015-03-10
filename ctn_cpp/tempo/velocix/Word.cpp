#include "Word.h"

#include <cctype>
#include <cassert>
#include <cstdio>

#define MAX_WORD_LENGHT 25

Word::Word()
: text_(NULL)
{
}

Word::Word(const Word& lhs)
: text_(NULL)
{
	unsigned int strsize = strlen(lhs.text_)+1; // including \0 character
	text_ = new char[strsize];
	for (size_t i = 0; i < strsize; ++i)
	{
		text_[i]= lhs.text_[i];
	}
}
Word& Word::operator=(const Word& lhs)
{
	if (text_ != NULL) delete[] text_; text_ = NULL;
	
	unsigned int strsize = strlen(lhs.text_) + 1; // including \0 character
	text_ = new char[strsize];
	for (size_t i = 0; i < strsize; ++i)
	{
		text_[i] = lhs.text_[i];
	}
	return *this;
}


Word::~Word()
{
	if (text_ != NULL)
		delete[] text_;
	text_ = NULL;
}

bool Word::empty() const
{
	return ((text_ == NULL));
}

const char* Word::get_text() const
{
	assert(text_ != NULL);
	return text_;
}

bool Word::operator==(const Word& lhs) const
{
	assert( !empty() && !lhs.empty() );
	bool not_equal = (strcmp(text_, lhs.text_));//strcmp return zero if equal, convert to bool is a false
	return !not_equal;
}
bool Word::operator!=(const Word& lhs) const
{
	assert(!empty() && !lhs.empty());
	bool not_equal = (strcmp(text_, lhs.text_));//strcmp return zero if equal, convert to bool is a false
	return not_equal;
}


bool Word::is_Symbol(const char& c) const
{
	if (isalpha(c)) return false;

	return true;
}

std::ostream& operator<<(std::ostream &os, const Word& word)
{
	if (!word.empty())
		os << "["<< word.get_text()<<"]";
	return os;
}

std::istream& operator>>(std::istream &ifs, Word& word)
{
	// clear text_
	// read the stream into a buffer (exluding all symbol, blank)
	// newly allocated text word
	// copy buffer to text word

	// clear older text
	if (word.text_ != NULL)
	{
		delete[] word.text_;
		word.text_ = NULL;
	}

	unsigned int word_size = 0;

	char text_buffer[MAX_WORD_LENGHT];

	// read stream to buffer
	while (ifs.good())
	{
		char c = ' ';
		ifs.get(c);
		// ctntodo
		// careful with words of pattern '  "John's"
		// to convert cap letter to min letters ??

		if (word.is_Symbol(c)) break; // todo not only blank break, but all symbol character

		text_buffer[word_size] = c;
		++word_size;
	}

	if (word_size > 0)
	{

		text_buffer[word_size] = '\0';	++word_size;

		// allocated new text word
		word.text_ = new char[word_size];

		// copy buffer to text word
		for (size_t i = 0; i < word_size; ++i)
		{
			word.text_[i] = text_buffer[i];
		}
	}

	return ifs;
}


