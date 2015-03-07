#include "VMinterpreter.h"
#include <iostream>
#include <cassert>

VMinterpreter::VMinterpreter(VMimage& vm)
	: ip_(0)
	, sp_(vm.size())
	, vm_data_(vm)
{
	//do not interpret empty data ctntodo exception here
	assert(sp_ > 0);
}

void VMinterpreter::process()
{
	
}



std::ostream& operator<<(std::ostream& os, const VMinterpreter& vmInterpreter)
{
	os << "ip." << vmInterpreter.ip_ << "	sp." << vmInterpreter.sp_;
	return os;
}
