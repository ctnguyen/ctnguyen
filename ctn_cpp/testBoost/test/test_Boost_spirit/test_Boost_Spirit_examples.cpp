#define BOOST_TEST_MODULE test_Boost_Spirit_examples
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

/// employee
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <complex>


namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    ///////////////////////////////////////////////////////////////////////////
    //  Our employee struct
    ///////////////////////////////////////////////////////////////////////////
    //[tutorial_employee_struct
    struct employee
    {
        int age;
        std::string surname;
        std::string forename;
        double salary;
    };
    //]
}
// We need to tell fusion about our employee struct
// to make it a first-class fusion citizen. This has to
// be in global scope.

//[tutorial_employee_adapt_struct
BOOST_FUSION_ADAPT_STRUCT(
    client::employee,
    (int, age)
    (std::string, surname)
    (std::string, forename)
    (double, salary)
)
//]

namespace client
{
    ///////////////////////////////////////////////////////////////////////////////
    //  Our employee parser
    ///////////////////////////////////////////////////////////////////////////////
    //[tutorial_employee_parser
    template <typename Iterator>
    struct employee_parser : qi::grammar<Iterator, employee(), ascii::space_type>
    {
        employee_parser() : employee_parser::base_type(start)
        {
            using qi::int_;
            using qi::lit;
            using qi::double_;
            using qi::lexeme;
            using ascii::char_;

            quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];

            start %=
                lit("employee")
                >> '{'
                >>  int_ >> ','
                >>  quoted_string >> ','
                >>  quoted_string >> ','
                >>  double_
                >>  '}'
                ;
        }

        qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
        qi::rule<Iterator, employee(), ascii::space_type> start;
    };
    //]
}

BOOST_AUTO_TEST_SUITE(All_examples)

#pragma region Example 
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
    const std::string str = "hello this is a string\nTo test word count functor";
    
    // create the token definition instance needed to invoke the lexical analyzer
    word_count_tokens<lex::lexertl::lexer<> > word_count_functor;

        // tokenize the given string, the bound functor gets invoked for each of 
    // the matched tokens
    char const* first = str.c_str();
    char const* last = &first[str.size()];
    bool r = lex::tokenize(first, last, word_count_functor, boost::bind(counter(), _1, boost::ref(c), boost::ref(w), boost::ref(l)));
}
#pragma endregion word_count_functor ////////////////////////////////////////////////////////////////////////////

#pragma region Example 

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
struct word_count_tokens_lexer : lex::lexer < Lexer >
{
    word_count_tokens_lexer()
        : c(0), w(0), l(0)
        , word("[^ \t\n]+")     // define tokens
        , eol("\n")
        , any(".")
    {
        using boost::spirit::lex::_start;
        using boost::spirit::lex::_end;
        using boost::phoenix::ref;

        // associate tokens with the lexer
        this->self = word[++ref(w), ref(c) += distance(_start, _end)] | eol[++ref(c), ++ref(l)] | any[++ref(c)] ;
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
    word_count_tokens_lexer<lexer_type> word_count_lexer;

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

#pragma endregion word_count_lexer ////////////////////////////////////////////////////////////////////////////

#pragma region Example 

BOOST_AUTO_TEST_CASE(employee)
{
    std::cout << "/////////////////////////////////////////////////////////\n\n";
    std::cout << "\t\tAn employee parser for Spirit...\n\n";
    std::cout << "/////////////////////////////////////////////////////////\n\n";

    std::cout
        << "Give me an employee of the form :"
        << "employee{age, \"surname\", \"forename\", salary } \n";
    std::cout << "Type [q or Q] to quit\n\n";

    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef client::employee_parser<iterator_type> employee_parser;

    employee_parser g; // Our grammar
    std::string str = "employee{1,\"mySurname1\", \"myForename1\",1000}\nemployee{2,\"mySurname2\", \"myForename2\",2000}";
    //while(getline(std::cin, str))
    //{
    //if(str.empty() || str[0] == 'q' || str[0] == 'Q')
    //    break;

    client::employee emp1;
    client::employee emp2;
    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    bool r1 = phrase_parse(iter, end, g, space, emp1);
    bool r2 = phrase_parse(iter, end, g, space, emp2);

    if(r1 && iter == end)
    {
        std::cout << boost::fusion::tuple_open('[');
        std::cout << boost::fusion::tuple_close(']');
        std::cout << boost::fusion::tuple_delimiter(", ");

        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "got: " << boost::fusion::as_vector(emp1) << std::endl;
        std::cout << "\n-------------------------\n";
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }
    //}

    std::cout << "Bye... :-) \n\n";
}

#pragma endregion employee ////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE_END()