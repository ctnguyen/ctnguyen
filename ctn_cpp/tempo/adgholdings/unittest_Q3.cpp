#define BOOST_TEST_MODULE interview_test_adgholdings

#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

#include "Question3.h"
BOOST_AUTO_TEST_SUITE(test_Question3)

BOOST_AUTO_TEST_CASE(test_first_test)
{
	const std::vector<int> price_data = Q3::generate_data();
	//Q3::PrintData(price_data);//ctndebug
	
	clock_t start_my_algo = std::clock();
	const unsigned int my_profit = Q3::GetMaxProfit(price_data);
	clock_t end_my_algo = std::clock();
	double my_algo_time = double(end_my_algo - start_my_algo) / CLOCKS_PER_SEC;


	// profit found by std
	clock_t start_std_algo = std::clock();
	const int max_price = *std::max_element(price_data.begin(), price_data.end());
	const int min_price = *std::min_element(price_data.begin(), price_data.end());
	const unsigned int std_profit = max_price - min_price;
	clock_t end_std_algo = std::clock();
	double std_algo_time = double(end_std_algo - start_std_algo) / CLOCKS_PER_SEC;

	//std::cout << "My Profit =" << my_profit << "  time " << std::setprecision(9)<< my_algo_time << std::endl
	//	<< "STD profit=" << std_profit << "  time " << std::setprecision(9)<< my_algo_time << std::endl;//ctndebug
	BOOST_CHECK(my_profit == std_profit);
	BOOST_CHECK(my_algo_time <= std_algo_time);
}

BOOST_AUTO_TEST_SUITE_END()
