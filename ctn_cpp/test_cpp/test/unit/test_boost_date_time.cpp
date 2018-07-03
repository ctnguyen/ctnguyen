/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#define BOOST_TEST_MODULE test_boost_date_time
#include <boost/test/unit_test.hpp>

/* Demonstrate conversions between a local time and utc
   * Output:
   *
   * UTC <--> New York while DST is NOT active (5 hours)
   * 2001-Dec-31 19:00:00 in New York is 2002-Jan-01 00:00:00 UTC time
   * 2002-Jan-01 00:00:00 UTC is 2001-Dec-31 19:00:00 New York time
   *
   * UTC <--> New York while DST is active (4 hours)
   * 2002-May-31 20:00:00 in New York is 2002-Jun-01 00:00:00 UTC time
   * 2002-Jun-01 00:00:00 UTC is 2002-May-31 20:00:00 New York time
   *
   * UTC <--> Arizona (7 hours)
   * 2002-May-31 17:00:00 in Arizona is 2002-Jun-01 00:00:00 UTC time
   */

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(all_date_time)

using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::local_time;

/** Keep using posix datetime on the server and saved into the DB
 *  The format input/output should be consistent, i.e yyyy-MM-dd hh:mm:ss.zzzzz IN THE C++ code
 *  When store to the db, it could be different
 *  When populate to the frontend, it could be different.
 *
 */
BOOST_AUTO_TEST_CASE(current_posix_time)
{
    //// Fundamental : date is considered as a time point
    ////               time of the day is considered as a duration (offset from 2 time point)
    const boost::posix_time::ptime currentDateTime = boost::date_time::microsec_clock<boost::posix_time::ptime>::universal_time();

    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(posix_time_str)
{
    //// Fundamental : date is considered as a time point
    ////               time of the day is considered as a duration (offset from 2 time point)
    const ptime utcDateTime1 (date(2018,Feb,16),time_duration(15,03,33,123456));
    const date utcDate = utcDateTime1.date();                 /// Time point
    const time_duration utcTime = utcDateTime1.time_of_day(); /// Duration

    BOOST_CHECK_EQUAL("2018-Feb-16 15:03:33.123456", boost::posix_time::to_simple_string(utcDateTime1));
    BOOST_CHECK_EQUAL("20180216T150333.123456", boost::posix_time::to_iso_string(utcDateTime1));
    BOOST_CHECK_EQUAL("2018-02-16T15:03:33.123456", boost::posix_time::to_iso_extended_string(utcDateTime1));

    BOOST_CHECK_EQUAL("2018-Feb-16", boost::gregorian::to_simple_string(utcDate));
    BOOST_CHECK_EQUAL("20180216", boost::gregorian::to_iso_string(utcDate));
    BOOST_CHECK_EQUAL("2018-02-16", boost::gregorian::to_iso_extended_string(utcDate));// TO use for date only

    BOOST_CHECK_EQUAL("15:03:33.123456", boost::posix_time::to_simple_string(utcTime)); // To use for time only
    BOOST_CHECK_EQUAL("150333.123456", boost::posix_time::to_iso_string(utcTime));

    ptime utcDateTime2 = time_from_string("2018-02-16 15:03:33.123456");
    BOOST_CHECK_EQUAL(utcDateTime1, utcDateTime2);
}

BOOST_AUTO_TEST_CASE(posix_time_io)
{   
    {
        boost::posix_time::time_facet* output_facet = new boost::posix_time::time_facet();
        std::stringstream ss;
        output_facet->format("%Y-%m-%d %H:%M:%S.%f");
        ss.imbue(std::locale(std::locale::classic(), output_facet));

        const std::string iDatetimeStr("2017-11-15 16:42:12.123456");// To use
        ptime datetime(time_from_string(iDatetimeStr));
        ss << datetime;
        const std::string oDatetimeStr = ss.str();
        BOOST_CHECK_EQUAL(iDatetimeStr, oDatetimeStr);
    }

    /// IO for simple string date
    {
        date_facet* output_facet = new date_facet();
        std::stringstream ss;
        output_facet->format("%Y-%m-%d");
        ss.imbue(std::locale(std::locale::classic(), output_facet));
        const std::string iDateStr("2017-11-15");
        date mydate(from_string(iDateStr));
        ss << mydate;
        const std::string oDateStr = ss.str();
        BOOST_CHECK_EQUAL(iDateStr, oDateStr);
    }
    
    /// IO for simple string time
    {
        const std::string iTimeStr("16:42:12.123456");
        time_duration mTime(duration_from_string(iTimeStr));
        const std::string oTimeStr = to_simple_string(mTime);
        BOOST_CHECK_EQUAL(iTimeStr, oTimeStr);
    }
}

BOOST_AUTO_TEST_CASE(convert_to_time_since_epoch)
{
    {  /// One microsecond
        const std::string epochDateTimeStr("1970-01-01 00:00:00.000000");
        const std::string firstDateTimeStr("1970-01-01 00:00:00.000001");
        const ptime epochDatetime(time_from_string(epochDateTimeStr));
        const ptime firstDatetime(time_from_string(firstDateTimeStr));
        const time_duration timeDiff = firstDatetime- epochDatetime;
        long timestamps = timeDiff.total_microseconds();
        BOOST_CHECK_EQUAL(timestamps, 1);
    }
}

BOOST_AUTO_TEST_CASE(conversion_utc_local)
{
    //This local adjustor depends on the machine TZ settings-- highly dangerous!
    typedef boost::date_time::c_local_adjustor<ptime> local_adj;
    ptime t10(date(2002, Jan, 1), hours(7));
    ptime t11 = local_adj::utc_to_local(t10);
    std::cout << "UTC <--> Zone base on TZ setting" << std::endl;
    std::cout << to_simple_string(t11) << " in your TZ is "
        << to_simple_string(t10) << " UTC time "
        << std::endl;
    time_duration td = t11 - t10;
    std::cout << "A difference of: "
        << to_simple_string(td) << std::endl;


    //eastern timezone is utc-5
    typedef boost::date_time::local_adjustor<ptime, -5, us_dst> us_eastern;

    ptime t1(date(2001, Dec, 31), hours(19)); //5 hours b/f midnight NY time

    std::cout << "\nUTC <--> New York while DST is NOT active (5 hours)"
        << std::endl;
    ptime t2 = us_eastern::local_to_utc(t1);
    std::cout << to_simple_string(t1) << " in New York is "
        << to_simple_string(t2) << " UTC time "
        << std::endl;

    ptime t3 = us_eastern::utc_to_local(t2);//back should be the same
    std::cout << to_simple_string(t2) << " UTC is "
        << to_simple_string(t3) << " New York time "
        << "\n\n";

    ptime t4(date(2002, May, 31), hours(20)); //4 hours b/f midnight NY time
    std::cout << "UTC <--> New York while DST is active (4 hours)" << std::endl;
    ptime t5 = us_eastern::local_to_utc(t4);
    std::cout << to_simple_string(t4) << " in New York is "
        << to_simple_string(t5) << " UTC time "
        << std::endl;

    ptime t6 = us_eastern::utc_to_local(t5);//back should be the same
    std::cout << to_simple_string(t5) << " UTC is "
        << to_simple_string(t6) << " New York time "
        << "\n" << std::endl;


    //Arizona timezone is utc-7 with no dst
    typedef boost::date_time::local_adjustor<ptime, -7, no_dst> us_arizona;

    ptime t7(date(2002, May, 31), hours(17));
    std::cout << "UTC <--> Arizona (7 hours)" << std::endl;
    ptime t8 = us_arizona::local_to_utc(t7);
    std::cout << to_simple_string(t7) << " in Arizona is "
        << to_simple_string(t8) << " UTC time "
        << std::endl;

}

BOOST_AUTO_TEST_SUITE_END()