/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test_rapidJSON
#include <boost/test/unit_test.hpp>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <iostream>

BOOST_AUTO_TEST_SUITE(all_rapidJSON)

BOOST_AUTO_TEST_CASE(simple_case)
{
    // 1. Parse a JSON string into DOM.
    const std::string jsonStr = "{\"project\":\"crypto\",\"exchanges\":3}";
    rapidjson::Document d;
    d.Parse(jsonStr.c_str());

    const bool hasProjectKey = d.HasMember("project");
    rapidjson::Value& pVal = d["project"];
    const std::string projectName = pVal.GetString();
    
    const bool hasExchangeKey = d.HasMember("exchanges");
    rapidjson::Value& eVal = d["exchanges"];
    const int nbExchange = eVal.GetInt();
    
    const bool hasTotoKey = d.HasMember("toto");
    BOOST_CHECK(hasProjectKey);
    BOOST_CHECK(hasExchangeKey);
    BOOST_CHECK(!hasTotoKey);
    BOOST_TEST( projectName == "crypto" , boost::test_tools::per_element() );
    BOOST_TEST(nbExchange,3);


    // 3. Stringify the DOM
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    const std::string recoverStr = buffer.GetString();
    BOOST_TEST( recoverStr == jsonStr , boost::test_tools::per_element() );
}

BOOST_AUTO_TEST_CASE(no_key_case)
{
    const std::string jsonStr = "[12,[13,14,15]]";
    rapidjson::Document d;
    d.Parse(jsonStr.c_str());

    BOOST_CHECK(d.IsArray());
    const rapidjson::Value& e0 = d[0];
    BOOST_CHECK(e0.IsInt());
    BOOST_TEST(e0.GetInt(),12);

    const rapidjson::Value& e1 = d[1];
    BOOST_CHECK(e1.IsArray());
    BOOST_TEST(e1[0].GetInt(),13);
    BOOST_TEST(e1[1].GetInt(),14);
    BOOST_TEST(e1[2].GetInt(),15);
}

BOOST_AUTO_TEST_CASE(test_performance)
{
    BOOST_CHECK(true);
    // TODO : generate a lot of json, and test parsing it into plateform object, check the total parsing time. It will give the idea of how much it take to parse data feed
    //        The best way is to generate all possible message type from different exchange, and parse all of them to have relevant benchmark
}

BOOST_AUTO_TEST_SUITE_END()