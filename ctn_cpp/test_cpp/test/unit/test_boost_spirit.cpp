/****************************************************** *
*  Date             09/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test_boost_spirit
#include <boost/test/unit_test.hpp>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>

namespace client
{
    namespace x3 = boost::spirit::x3;
    using x3::_attr;

    struct print_action
    {
        template <typename Context>
        void operator()(Context const& ctx) const
        {
            std::cout << _attr(ctx) << std::endl;
        }
    };
}

namespace client { namespace ast
{
    ///////////////////////////////////////////////////////////////////////////
    //  Our employee struct
    ///////////////////////////////////////////////////////////////////////////
    struct employee
    {
        int age;
        std::string surname;
        std::string forename;
        double salary;
    };

    using boost::fusion::operator<<;
}}

// We need to tell fusion about our employee struct
// to make it a first-class fusion citizen. This has to
// be in global scope.

BOOST_FUSION_ADAPT_STRUCT(client::ast::employee,
    age, surname, forename, salary
)

namespace client
{
    ///////////////////////////////////////////////////////////////////////////////
    //  Our employee parser
    ///////////////////////////////////////////////////////////////////////////////
    namespace parser
    {
        namespace x3 = boost::spirit::x3;
        namespace ascii = boost::spirit::x3::ascii;

        using x3::int_;
        using x3::lit;
        using x3::double_;
        using x3::lexeme;
        using ascii::char_;

        x3::rule<class employee, ast::employee> const employee = "employee";

        auto const quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];

        auto const employee_def =
            lit("employee")
            >> '{'
            >>  int_ >> ','
            >>  quoted_string >> ','
            >>  quoted_string >> ','
            >>  double_
            >>  '}'
            ;

        BOOST_SPIRIT_DEFINE(employee);
    }
}

BOOST_AUTO_TEST_SUITE(all_spirit)


BOOST_AUTO_TEST_CASE(empty_test)
{
    using boost::spirit::x3::int_;
    using boost::spirit::x3::parse;
    using client::print_action;

    { // example using function object

        char const *first = "{43}", *last = first + std::strlen(first);
        parse(first, last, '{' >> int_[print_action()] >> '}');
    }

    { // example using C++14 lambda

        char const *first = "{44}", *last = first + std::strlen(first);
        auto f = [](auto& ctx){
            auto attrctx = _attr(ctx);
            std::cout << _attr(ctx) << std::endl; 
        };
        parse(first, last, '{' >> int_[f] >> '}');
    }

    BOOST_CHECK(true);
}


BOOST_AUTO_TEST_CASE(example_employee)
{
    using boost::spirit::x3::ascii::space;
    typedef std::string::const_iterator iterator_type;
    using client::parser::employee;

    std::string str = "employee{15, \"surname\", \"forename\", 70 } \n"; 

    client::ast::employee emp;
    iterator_type iter = str.begin();
    iterator_type const end = str.end();
    bool r = phrase_parse(iter, end, employee, space, emp);

    if (r && iter == end)
    {
        std::cout << boost::fusion::tuple_open('[');
        std::cout << boost::fusion::tuple_close(']');
        std::cout << boost::fusion::tuple_delimiter(", ");

        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "got: " << emp << std::endl;
        std::cout << "\n-------------------------\n";
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }

    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()