/*!
 * helper.h
 */
#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <iostream>
#include <queue>

namespace helper
{

struct Greater
{
    bool operator() ( int i, int j)
    {
    	return i > j;
    }
} greater;

}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v)
{
	for(size_t i=0;i<v.size();++i)
		std::cout<<v[i]<<"  ";

	return os;
}

#endif /* HELPER_H */
