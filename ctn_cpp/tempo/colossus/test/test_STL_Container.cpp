#define BOOST_TEST_MODULE colossus_test_STL

#include <iostream>
#include <fstream>
#include <ctime>

#include <boost/test/included/unit_test.hpp>

#include "helper.h"

struct STL_Container
{
	STL_Container()
    {
    	v.push_back(2);
    	v.push_back(4);
    	v.push_back(-15);
    	v.push_back(4);
    	v.push_back(98);
    	v.push_back(2);
    	v.push_back(4);
    }

    std::vector<int> v;
};

BOOST_FIXTURE_TEST_CASE( sort_vector1, STL_Container )
{
	std::sort(v.begin(), v.end());
	//std::cout<<v<<std::endl;
}

BOOST_FIXTURE_TEST_CASE( sort_vector2, STL_Container )
{
	std::sort(v.begin(), v.end(), helper::greater);
	//std::cout<<v<<std::endl;
}

BOOST_FIXTURE_TEST_CASE( test_maxHeap, STL_Container )
{
	std::priority_queue<int> maxHeap;

	for(size_t i=0;i<v.size();++i )
	{
		maxHeap.push(v[i]);
	}

    std::vector<int> heap_vectorized;

    while ( !maxHeap.empty())
    {
    	heap_vectorized.push_back(maxHeap.top() ) ; maxHeap.pop();
    }
    std::sort(v.begin(), v.end(),helper::greater);

    BOOST_CHECK( heap_vectorized.size() == v.size() );

    for(size_t i=0;i<v.size();++i)
    {
    	BOOST_CHECK( heap_vectorized[i] == v[i] );
    }

    //std::cout<<v<<std::endl;
	//std::cout<<heap_vectorized<<std::endl;
}

BOOST_FIXTURE_TEST_CASE( test_minHeap, STL_Container )
{
	//std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap;
	std::priority_queue<int, std::vector<int>, helper::Greater > minHeap;

	for(size_t i=0;i<v.size();++i )
	{
		minHeap.push(v[i]);
	}

    std::vector<int> heap_vectorized;

    while ( !minHeap.empty())
    {
    	heap_vectorized.push_back(minHeap.top() ) ; minHeap.pop();
    }
    std::sort(v.begin(), v.end());

    BOOST_CHECK( heap_vectorized.size() == v.size() );

    for(size_t i=0;i<v.size();++i)
    {
    	BOOST_CHECK( heap_vectorized[i] == v[i] );
    }

    std::cout<<v<<std::endl;
	std::cout<<heap_vectorized<<std::endl;
}
