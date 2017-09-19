#define BOOST_TEST_MODULE test_Boost_Spirit_AQL
#include <boost/test/unit_test.hpp>

#pragma warning(push) //// Warning disabling wrapper : http://stackoverflow.com/questions/34709284/how-do-i-deal-with-warnings-generated-by-boost-spirit
#pragma warning(disable : 4348)
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#pragma warning(pop)

//#include <boost/spirit/home/x3.hpp>

#include <iostream>
#include <string>
#include <vector>

/** Try to make a QueryManager, aiming to translate from AQL query to any other query, with any database.
 *
 *  The first task to do is to understand how the parser work, identify different component of the AQL query
 *  Second part is from the parsed component, how to build the action to do
 *
 *
 */
namespace QueryManager
{
}



//namespace client
//{
//    namespace x3 = boost::spirit::x3;
//    namespace ascii = boost::spirit::x3::ascii;
//
//    ///////////////////////////////////////////////////////////////////////////
//    //  Our number list parser
//    ///////////////////////////////////////////////////////////////////////////
//    template <typename Iterator>
//    bool parse_numbers(Iterator first, Iterator last)
//    {
//        using x3::double_;
//        using x3::phrase_parse;
//        using ascii::space;
//
//        bool r = phrase_parse(
//            first,                          // Start Iterator
//            last,                           // End Iterator
//            double_ >> *(',' >> double_),   // The Parser
//            space                           // The Skip-Parser
//        );
//        if (first != last) // fail if we did not get a full match
//            return false;
//        return r;
//    }
//}

BOOST_AUTO_TEST_SUITE(All_Types)

BOOST_AUTO_TEST_CASE(test_parse_assignment)
{
    using boost::spirit::qi::double_;
    using boost::spirit::qi::_1;
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::ascii::space;
    using boost::phoenix::ref;

    double outputNb1;
    double outputNb2;
    std::string str = "1.23 4.56";
    const bool successParse = phrase_parse( str.begin()
                                          , str.end()
                                          , double_[ref(outputNb1)=_1]  >> double_[ref(outputNb2)=_1]
                                          , space);
    BOOST_CHECK(successParse);
    BOOST_CHECK(outputNb1 == 1.23);
    BOOST_CHECK(outputNb2 == 4.56);
}

BOOST_AUTO_TEST_CASE(test_parse_complex)
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
    using qi::double_;
    using qi::phrase_parse;
    using ascii::space;

    std::string str = "(1.584, 2.798)";
    const bool successParse = phrase_parse( str.begin()
                                          , str.end()
                                          , '(' >> double_ >> ',' >> double_ >> ')' 
                                          , space);
    BOOST_CHECK(successParse);
}

BOOST_AUTO_TEST_CASE(test_parse_AQL)
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
    using qi::double_;
    using qi::phrase_parse;
    using ascii::space;

    std::string str = "[1.584, 2.798]";
    const bool successParse = phrase_parse( str.begin()
                                          , str.end()
                                          , '[' >> double_ >> ',' >> double_ >> ']' 
                                          , space);
    BOOST_CHECK(successParse);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// TEST X3 TEST X3 TEST X3 TEST X3 TEST X3 TEST X3 TEST X3 TEST X3 TEST X3  //

BOOST_AUTO_TEST_SUITE_END()
