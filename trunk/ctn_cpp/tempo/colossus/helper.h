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

}

inline std::ostream& operator<<(std::ostream& os, const std::vector<int>& v)
{
	for(size_t i=0;i<v.size();++i) 
		std::cout<<v[i]<<"  ";
	return os;
}

#endif /* HELPER_H */
