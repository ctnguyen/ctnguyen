/*!
 * Operator.h
 */
#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Helper.h"
#include "VMimage.h"

/*! \class Operator
 *  Operator hold reference to data and operate on these data
 */
class BaseOperator
{
public :

	BaseOperator(helper::Int32& ip, helper::Int32& sp, VMimage& data)
	: ip_(ip), sp_(sp), data_(data){}
	
	const std::string& name() const { return name_; }

	// to implemente for concrete operator
	virtual bool execute(const helper::InstructionData& instruction) = 0;

protected :
	
	helper::Int32& ip_;
	helper::Int32& sp_;
	VMimage& data_;
	std::string name_; // ctntodo to remove and use function name() return by value string

	void f(const helper::Int32& v) const
	{
		--sp_; data_[sp_] = v;
	}
	
	helper::Int32 g() const
	{
		const helper::Int32 v = data_[sp_]; ++sp_; return v;
	}
};

class _True_0 : public BaseOperator
{
public:
	_True_0(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _True_1 : public BaseOperator
{
public:
	_True_1(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _True_2 : public BaseOperator
{
public:
	_True_2(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _True_3 : public BaseOperator
{
public:
	_True_3(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _True_4 : public BaseOperator
{
public:
	_True_4(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _True_5 : public BaseOperator
{
public:
	_True_5(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _True_6 : public BaseOperator
{
public:
	_True_6(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _True_7 : public BaseOperator
{
public:
	_True_7(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _True_8 : public BaseOperator
{
public:
	_True_8(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_0 : public BaseOperator
{
public:
	_False_0(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_1 : public BaseOperator
{
public:
	_False_1(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_2 : public BaseOperator
{
public:
	_False_2(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_3 : public BaseOperator
{
public:
	_False_3(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_4 : public BaseOperator
{
public:
	_False_4(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_5 : public BaseOperator
{
public:
	_False_5(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_6 : public BaseOperator
{
public:
	_False_6(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_7 : public BaseOperator
{
public:
	_False_7(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_8 : public BaseOperator
{
public:
	_False_8(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_9 : public BaseOperator
{
public:
	_False_9(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};

class _False_10 : public BaseOperator
{
public :
	_False_10(helper::Int32& ip, helper::Int32& sp, VMimage& data);
	virtual bool execute(const helper::InstructionData& instruction);
};




struct OperatorFactory
{
	OperatorFactory(helper::Int32& ip, helper::Int32& sp, VMimage& data);

	std::unique_ptr<BaseOperator> operator()(bool binop, const helper::Int32& opt_item);

private:

	helper::Int32& ip_;
	helper::Int32& sp_;
	VMimage& data_;
};

#endif /* OPERATOR_H */
