#include "VMinterpreter.h"
#include "Operator.h"
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
	OperatorFactory operator_factory(ip_,sp_,vm_data_);
	bool is_stop = false;
	while (!is_stop)
	{
		const helper::Int32 current_instruction = vm_data_[ip_];
		++ip_;
		const helper::InstructionData instruction_data = helper::decode(current_instruction);

		const helper::Int32 operation_item = helper::convertBinary7ToInt32(instruction_data.operation);

		std::unique_ptr<BaseOperator> m_operator = operator_factory(instruction_data.binop, operation_item);
		is_stop = m_operator->execute(instruction_data);
		
		const std::string& op_name = m_operator->name();
#ifdef CTN_BUILD_TEST
		std::cout << "	" << op_name << std::endl;// << "		" << *this << std::endl;
#endif
	}
}



std::ostream& operator<<(std::ostream& os, const VMinterpreter& vmInterpreter)
{
	os << "ip." << vmInterpreter.ip_ << "	sp." << vmInterpreter.sp_;
	return os;
}
