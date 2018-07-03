/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test_boost_dll
#include <boost/test/unit_test.hpp>
#include <boost/dll.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE(all_boost_dll_test)

BOOST_AUTO_TEST_CASE(current_posix_time)
{
    const boost::filesystem::path execPath = boost::dll::program_location();
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()