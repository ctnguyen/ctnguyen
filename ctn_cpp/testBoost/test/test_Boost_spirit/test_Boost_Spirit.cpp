#define BOOST_TEST_MODULE test_Boost_Spirit
#include <boost/test/unit_test.hpp>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    ///////////////////////////////////////////////////////////////////////////
    //  Our number list parser
    ///////////////////////////////////////////////////////////////////////////
    //[tutorial_numlist1
    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<double>& v)
    {
        using qi::double_;
        using qi::phrase_parse;
        using ascii::space;

        bool r = phrase_parse(
            first,                          /*< start iterator >*/
            last,                           /*< end iterator >*/
            double_ >> *('.' >> double_),   /*< the parser >*/
            space                           /*< the skip-parser >*/
        );
        if (first != last) // fail if we did not get a full match
            return false;
        return r;
    }
    //]
}

BOOST_AUTO_TEST_SUITE(All_Types)

BOOST_AUTO_TEST_CASE(num_list1)
{
    const std::string two_numbers = "2.1587452187695 1459876532159.872";
    std::vector<double> values;
    const bool successParse = client::parse_numbers(two_numbers.begin(), two_numbers.end(), values);

    BOOST_CHECK(successParse);
}

BOOST_AUTO_TEST_SUITE_END()