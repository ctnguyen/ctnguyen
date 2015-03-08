#include "Operator.h"

#include <stdio.h> // getchar()
#include <cassert>

BaseOperator::BaseOperator(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: ip_(ip), sp_(sp), data_(data){}

void BaseOperator::f(const helper::Int32& v) const
{
	assert(sp_ > 0); // push iff sp > 0
	--sp_; data_[sp_] = v;
}

helper::Int32 BaseOperator::g() const
{
	assert( sp_ < data_.size() ); // pop iff sp < data size
	const helper::Int32 v = data_[sp_]; ++sp_; return v;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
_True_0::_True_0(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: BaseOperator(ip,sp,data)
{
	name_ = "add";
}

bool _True_0::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 b = g();
	const helper::Int32 a = g();
	f(a + b);
	return false;
}

_True_1::_True_1(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: BaseOperator(ip, sp, data)
{
	name_ = "sub";
}

bool _True_1::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 b = g();
	const helper::Int32 a = g();
	f(a - b);
	return false;
}

_True_2::_True_2(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: BaseOperator(ip, sp, data)
{
	name_ = "mul";
}

bool _True_2::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 b = g();
	const helper::Int32 a = g();
	f(a * b);
	return false;
}

_True_3::_True_3(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: BaseOperator(ip, sp, data)
{
	name_ = "div";
}

bool _True_3::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 b = g();
	const helper::Int32 a = g();
	f(a / b);
	return false;
}

_True_4::_True_4(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: BaseOperator(ip, sp, data)
{
	name_ = "and";
}

bool _True_4::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 b = g();
	const helper::Int32 a = g();
	f(a & b);
	return false;
}

_True_5::_True_5(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	name_ = "or";
}

bool _True_5::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 b = g();
	const helper::Int32 a = g();
	f(a | b);
	return false;
}

_True_6::_True_6(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	name_ = "xor";
}

bool _True_6::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 b = g();
	const helper::Int32 a = g();
	f(a ^ b);
	return false;
}

_True_7::_True_7(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	name_ = "eq";
}

bool _True_7::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 b = g();
	const helper::Int32 a = g();
	f(static_cast<helper::Int32>(a == b) );
	return false;
}

_True_8::_True_8(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: BaseOperator(ip, sp, data)
{
	name_ = "lt";
}

bool _True_8::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 b = g();
	const helper::Int32 a = g();
	f(static_cast<helper::Int32>(a == b) );
	return false;
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
_False_0::_False_0(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: BaseOperator(ip, sp, data)
{
	name_ = "pop";
}

bool _False_0::execute(const helper::InstructionData& instruction)
{
	++sp_;
	return false;
}

_False_1::_False_1(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: BaseOperator(ip, sp, data)
{
	name_ = "Name Is Not Defined";
}

bool _False_1::execute(const helper::InstructionData& instruction)
{
	helper::Int32 optional_data_int = helper::convertBinary24ToInt32(instruction.optdata);
	
	std::stringstream ss; ss << "push " << optional_data_int;
	name_ = ss.str();

	f(optional_data_int);	
	return false;
}

_False_2::_False_2(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	std::stringstream ss; ss << "push " << ip_;
	name_ = ss.str();
}

bool _False_2::execute(const helper::InstructionData& instruction)
{
	f(ip_);
	return false;
}

_False_3::_False_3(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	std::stringstream ss; ss << "push " << sp_;
	name_ = ss.str();
}

bool _False_3::execute(const helper::InstructionData& instruction)
{
	f(sp_);
	return false;
}

_False_4::_False_4(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	name_ = "load";
}

bool _False_4::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 addr = g() ;
	f(data_[addr]);
	return false;
}

_False_5::_False_5(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	name_ = "store";
}

bool _False_5::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 st_data = g();
	const helper::Int32 addr = g();
	data_[addr] = st_data;
	return false;
}

_False_6::_False_6(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	name_ = "jmp";
}

bool _False_6::execute(const helper::InstructionData& instruction)
{
	const helper::Int32 cond = g();
	const helper::Int32 addr = g();
	if (cond != 0)
	{
		ip_ = addr;
	}
	return false;
}

_False_7::_False_7(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	name_ = "not";
}

bool _False_7::execute(const helper::InstructionData& instruction)
{
	if (0 == g())
	{
		f(1);
	}	
	else
	{
		f(0);
	}
	return false;
}

_False_8::_False_8(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	name_ = "putc";
}

bool _False_8::execute(const helper::InstructionData& instruction)
{
	helper::Int32 left_int = g();
	helper::Int32 right_int = helper::convertHexStringToInt32("0xff");
	helper::Int32 and_int = (left_int & right_int);
	helper::Binary32 bin32 = helper::convertInt32ToBinary32(and_int);

	std::cout <<"--			-- special operator (false,8)  [" << bin32[0]<<"]" << std::endl;
	return false;
}

_False_9::_False_9(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: BaseOperator(ip, sp, data)
{
	name_ = "getc";
}

bool _False_9::execute(const helper::InstructionData& instruction)
{
	helper::Int32 input_int;
	input_int = getchar();
	const helper::Binary32 input_bin32 = helper::convertInt32ToBinary32(input_int);
	helper::Binary32 bin32; 
	bin32[0] = input_bin32[0];

	const helper::Int32 x32 = helper::convertBinary32ToInt32(bin32);
	const helper::Int32 hex_number = helper::convertHexStringToInt32("0xff");
	helper::Int32 and_int = (x32 & hex_number);
	f(and_int);

	return false;
}

_False_10::_False_10(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: BaseOperator(ip, sp, data)
{
	name_ = "halt";
}

bool _False_10::execute(const helper::InstructionData& instruction)
{
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
OperatorFactory::OperatorFactory(helper::Int32& ip, helper::Int32& sp, VMimage& data)
: ip_(ip), sp_(sp), data_(data)
{}

std::unique_ptr<BaseOperator> OperatorFactory::operator()(bool binop, const helper::Int32& opt_item)
{
	std::unique_ptr<BaseOperator> operator_ptr;
	if (binop) // true
	{
		assert(0<=opt_item && opt_item < 9);
		switch (opt_item)
		{
		case 0:
			operator_ptr.reset(new _True_0(ip_,sp_,data_) );
			break;
		case 1:
			operator_ptr.reset(new _True_1(ip_, sp_, data_));
			break;
		case 2:
			operator_ptr.reset(new _True_2(ip_, sp_, data_));
			break;
		case 3:
			operator_ptr.reset(new _True_3(ip_, sp_, data_));
			break;
		case 4:
			operator_ptr.reset(new _True_4(ip_, sp_, data_));
			break;
		case 5:
			operator_ptr.reset(new _True_5(ip_, sp_, data_));
			break;
		case 6:
			operator_ptr.reset(new _True_6(ip_, sp_, data_));
			break;
		case 7:
			operator_ptr.reset(new _True_7(ip_, sp_, data_));
			break;
		case 8:
			operator_ptr.reset(new _True_8(ip_, sp_, data_));
			break;
		default:
			throw("OperatorFactory can not create with these parameters");
		}
	}
	else // false
	{
		assert(0 <= opt_item && opt_item < 11);
		switch (opt_item)
		{
		case 0:
			operator_ptr.reset(new _False_0(ip_, sp_, data_));
			break;
		case 1:
			operator_ptr.reset(new _False_1(ip_, sp_, data_));
			break;
		case 2:
			operator_ptr.reset(new _False_2(ip_, sp_, data_));
			break;
		case 3:
			operator_ptr.reset(new _False_3(ip_, sp_, data_));
			break;
		case 4:
			operator_ptr.reset(new _False_4(ip_, sp_, data_));
			break;
		case 5:
			operator_ptr.reset(new _False_5(ip_, sp_, data_));
			break;
		case 6:
			operator_ptr.reset(new _False_6(ip_, sp_, data_));
			break;
		case 7:
			operator_ptr.reset(new _False_7(ip_, sp_, data_));
			break;
		case 8:
			operator_ptr.reset(new _False_8(ip_, sp_, data_));
			break;
		case 9:
			operator_ptr.reset(new _False_9(ip_, sp_, data_));
			break;
		case 10:
			operator_ptr.reset(new _False_10(ip_, sp_, data_));
			break;
		default:
			throw("OperatorFactory can not create with these parameters");
		}
	}

	return operator_ptr;
}
