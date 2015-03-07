/*!
 * VMimage.h
 */
#ifndef VM_IMAGE_H
#define VM_IMAGE_H

#include <iostream>
#include <vector>

#include "Helper.h"

/*! \class VMimage
 */
class VMimage
{
public :

	VMimage();

	void load();

private :
	
	helper::Int32 data_size_;
	std::vector<helper::Int32> data_;
};

#endif /* VM_IMAGE_H */
