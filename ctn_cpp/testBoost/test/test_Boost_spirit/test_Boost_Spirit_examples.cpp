#define BOOST_TEST_MODULE test_Boost_Spirit_examples
#include <boost/test/unit_test.hpp>

#pragma warning(push) //// Warning disabling wrapper : http://stackoverflow.com/questions/34709284/how-do-i-deal-with-warnings-generated-by-boost-spirit
#pragma warning(disable : 4348)
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#pragma warning(pop)
#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <iostream>
#include <string>

BOOST_AUTO_TEST_SUITE(All_examples)

//////////////////   TEST word_count_functor  ///////////////////////////////////////
namespace lex = boost::spirit::lex;
enum token_ids
{
    ID_WORD = 1000,
    ID_EOL,
    ID_CHAR
};

template <typename Lexer>
struct word_count_tokens : lex::lexer<Lexer>
{
    word_count_tokens()
    {
        // define tokens (the regular expression to match and the corresponding
        // token id) and add them to the lexer 
        this->self.add
            ("[^ \t\n]+", ID_WORD) // words (anything except ' ', '\t' or '\n')
            ("\n", ID_EOL)         // newline characters
            (".", ID_CHAR)         // anything else is a plain character
        ;
    }
};

struct counter
{
//<- this is an implementation detail specific to boost::bind and doesn't show 
//   up in the documentation
    typedef bool result_type;
//->
    // the function operator gets called for each of the matched tokens
    // c, l, w are references to the counters used to keep track of the numbers
    template <typename Token>
    bool operator()(Token const& t, std::size_t& c, std::size_t& w, std::size_t& l) const
    {
        switch (t.id()) {
        case ID_WORD:       // matched a word
        // since we're using a default token type in this example, every 
        // token instance contains a `iterator_range<BaseIterator>` as its token
        // attribute pointing to the matched character sequence in the input 
            ++w; c += t.value().size(); 
            break;
        case ID_EOL:        // matched a newline character
            ++l; ++c; 
            break;
        case ID_CHAR:       // matched something else
            ++c; 
            break;
        }
        return true;        // always continue to tokenize
    }
};

//////////////////   TEST word_count_functor  ///////////////////////////////////////


BOOST_AUTO_TEST_CASE(word_count_functor)
{
    // these variables are used to count characters, words and lines
    std::size_t c = 0, w = 0, l = 0;

    // input string
    const std::string str = "hello this is a string\nTo test word count functor";
    
    // create the token definition instance needed to invoke the lexical analyzer
    word_count_tokens<lex::lexertl::lexer<> > word_count_functor;

        // tokenize the given string, the bound functor gets invoked for each of 
    // the matched tokens
    char const* first = str.c_str();
    char const* last = &first[str.size()];
    bool r = lex::tokenize(first, last, word_count_functor, boost::bind(counter(), _1, boost::ref(c), boost::ref(w), boost::ref(l)));
}

BOOST_AUTO_TEST_SUITE_END()