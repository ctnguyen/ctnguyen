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

	helper::Int32 size() const;
	helper::Int32& operator[](size_t i);
	const helper::Int32& operator[](size_t i)const;

	void load(const char* file_path_name);

private :
	
	helper::Int32 data_size_;
	helper::Int32 image_size_;
	std::vector<helper::Int32> data_;
};

#endif /* VM_IMAGE_H */
