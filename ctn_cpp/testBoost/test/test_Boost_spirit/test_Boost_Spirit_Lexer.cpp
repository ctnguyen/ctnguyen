#define BOOST_TEST_MODULE test_Boost_Spirit_Lexer
#include <boost/test/unit_test.hpp>

#pragma warning(push) //// Warning disabling wrapper : http://stackoverflow.com/questions/34709284/how-do-i-deal-with-warnings-generated-by-boost-spirit
#pragma warning(disable : 4348)
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#pragma warning(pop)
#include <boost/bind.hpp>
#include <boost/ref.hpp>

/// word_count_lexer  ///////////////////////////////////////
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_algorithm.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <complex>


BOOST_AUTO_TEST_SUITE(lexer_examples)

/// word_count_functor  ///////////////////////////////////////
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

BOOST_AUTO_TEST_CASE(word_count_functor)
{
    // these variables are used to count characters, words and lines
    std::size_t c = 0, w = 0, l = 0;

    // input string
    //const std::string str = "hello this is a string\nTo test word count functor";
    const std::string str = "hello this is a string\t\nTo test word count functor";
    
    // create the token definition instance needed to invoke the lexical analyzer
    word_count_tokens<lex::lexertl::lexer<> > word_count_functor;

        // tokenize the given string, the bound functor gets invoked for each of 
    // the matched tokens
    char const* first = str.c_str();
    char const* last = &first[str.size()];
    bool r = lex::tokenize(first, last, word_count_functor, boost::bind(counter(), _1, boost::ref(c), boost::ref(w), boost::ref(l)));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct distance_func
{
    template <typename Iterator1, typename Iterator2>
    struct result : boost::iterator_difference < Iterator1 > {};

    template <typename Iterator1, typename Iterator2>
    typename result<Iterator1, Iterator2>::type
        operator()(Iterator1 const& begin, Iterator2 const& end) const
    {
        return std::distance(begin, end);
    }
};
boost::phoenix::function<distance_func> const distance = distance_func();

//[wcl_token_definition
template <typename Lexer>
struct word_count_tokens_action : lex::lexer < Lexer >
{
    word_count_tokens_action()
        : c(0), w(0), l(0)
        , word("[^ \t\n]+")     // define tokens
        , eol("\n")
        , any(".")
    {
        using boost::spirit::lex::_start;
        using boost::spirit::lex::_end;
        using boost::phoenix::ref;

        // associate tokens with the lexer
        this->self = word[++ref(w), ref(c) += distance(_start, _end)] 
                   | eol[++ref(c), ++ref(l)] 
                   | any[++ref(c)] ;
    }

    std::size_t c, w, l;
    lex::token_def<> word, eol, any;
};

BOOST_AUTO_TEST_CASE(word_count_lexer)
{
    /*<
    Specifying `omit` as the token attribute type generates a token class
    not holding any token attribute at all (not even the iterator range of the
    matched input sequence), therefore optimizing the token, the lexer, and
    possibly the parser implementation as much as possible. Specifying
    `mpl::false_` as the 3rd template parameter generates a token
    type and an iterator, both holding no lexer state, allowing for even more
    aggressive optimizations. As a result the token instances contain the token
    ids as the only data member.
    >*/
    typedef lex::lexertl::token < char const*, lex::omit, boost::mpl::false_ > token_type;

    /*<  This defines the lexer type to use>*/
    typedef lex::lexertl::actor_lexer<token_type> lexer_type;

    /*<  Create the lexer object instance needed to invoke the lexical analysis>*/
    word_count_tokens_action<lexer_type> word_count_lexer;

    /*<  Read input from the given file, tokenize all the input, while discarding
         all generated tokens
         >*/  // input string
    const std::string str = "hello this is a string\nTo test word count lexer";
    char const* first = str.c_str();
    char const* last = &first[str.size()];

    /*<  Create a pair of iterators returning the sequence of generated tokens
    >*/  lexer_type::iterator_type iter = word_count_lexer.begin(first, last);
    lexer_type::iterator_type end = word_count_lexer.end();

    /*<  Here we simply iterate over all tokens, making sure to break the loop
         if an invalid token gets returned from the lexer
         >*/  while(iter != end && token_is_valid(*iter))
    ++iter;

    if(iter == end)
    {
        std::cout << "lines: " << word_count_lexer.l
            << ", words: " << word_count_lexer.w
            << ", characters: " << word_count_lexer.c
            << "\n";
    }
    else
    {
        std::string rest(first, last);
        std::cout << "Lexical analysis failed\n" << "stopped at: \""
            << rest << "\"\n";
    }
}


BOOST_AUTO_TEST_SUITE_END()