/*! \author chithanhnguyen.math@gmail.com
 *
 *  21.Dec.2014
 *
 *  a set of example to understand smart pointer
 *
 */

#include <iostream>
#include <memory>


int main(int argc, char **argv)
{
	{ // Example of broken code when using 2 unique_ptr holding the same object
		int* pInt = new int(100);

		std::unique_ptr<int> p1(pInt);
		std::unique_ptr<int> p2(pInt);
	}

	std::shared_ptr<int> p3;


	return 0;
}
