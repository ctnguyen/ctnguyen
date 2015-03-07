/*!
 * VMinterpreter.h
 */
#ifndef VM_INTERPRETER_H
#define VM_INTERPRETER_H

#include <iostream>
#include "Helper.h"
#include "VMimage.h"


/*! \class VMinterpreter
 */
class VMinterpreter
{
public:

	VMinterpreter(VMimage& vm);

	// interpret the virtual image
	void process();
	
	// print state of interpreter to a stream
	friend std::ostream& operator<<(std::ostream& os, const VMinterpreter& vmInterpreter);
private :

	helper::Int32 ip_;
	helper::Int32 sp_;

	VMimage& vm_data_;
};

#endif /* VM_INTERPRETER_H */
