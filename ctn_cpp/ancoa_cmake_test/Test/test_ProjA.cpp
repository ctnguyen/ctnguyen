/**
 *	@file Test/test_Proj1.hpp
 *	@date June 2015
 */
#include <ProjA/ProjA.hpp>
#define BOOST_TEST_MODULE testProjA
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( constructor )
{
    ProjA projA;

    BOOST_CHECK(true);
}
