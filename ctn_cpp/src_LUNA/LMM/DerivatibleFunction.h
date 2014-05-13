#pragma once

#include <boost/function.hpp>
#include <boost/shared_array.hpp>
#include <boost/bind.hpp>
#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>

//! only operator available: "+", "-", "*", "/"
class CombineOperator
{
	std::string operatorName_;
public:
	CombineOperator(const std::string& operatorName):operatorName_(operatorName){}
	std::string get_operatorName() const {return operatorName_;}
};


//! YY TODO: need to implement copy constructor, assignment operator ... 
class CombinedDerivatibleFunction //: public DerivatibleFunction
{
	boost::shared_ptr<CombinedDerivatibleFunction> derivatibleFunction1_;
	boost::shared_ptr<CombinedDerivatibleFunction> derivatibleFunction2_;
	CombineOperator combineOperator_;
public:
	virtual double func(double x) const
	{
		if(combineOperator_.get_operatorName() == "+")
			return derivatibleFunction1_->func(x) + derivatibleFunction2_->func(x);
		if(combineOperator_.get_operatorName() == "-")
			return derivatibleFunction1_->func(x) - derivatibleFunction2_->func(x);
		if(combineOperator_.get_operatorName() == "*")
			return derivatibleFunction1_->func(x) * derivatibleFunction2_->func(x);
		if(combineOperator_.get_operatorName() == "/")
			return derivatibleFunction1_->func(x) / derivatibleFunction2_->func(x);
		throw("Error: operator not defined!");
	}

	virtual double firstDerivative(double x) const
	{
		if(combineOperator_.get_operatorName() == "+")
		{
			return derivatibleFunction1_->firstDerivative(x) + derivatibleFunction2_->firstDerivative(x);
		}
		if(combineOperator_.get_operatorName() == "-")
		{
			return derivatibleFunction1_->firstDerivative(x) - derivatibleFunction2_->firstDerivative(x);
		}
		if(combineOperator_.get_operatorName() == "*")
		{
			return derivatibleFunction1_->firstDerivative(x) * derivatibleFunction2_->func(x) 
					+  derivatibleFunction1_->func(x) * derivatibleFunction2_->firstDerivative(x);
		}
		if(combineOperator_.get_operatorName() == "/")
		{
			double numerator = derivatibleFunction1_->firstDerivative(x) * derivatibleFunction2_->func(x) 
				-  derivatibleFunction1_->func(x) * derivatibleFunction2_->firstDerivative(x);
			double denominator = derivatibleFunction2_->func(x)*derivatibleFunction2_->func(x);  
			return numerator/denominator;
		}
		throw("Error: operator not defined!");
	}

	virtual double secondDerivative(double x) const
	{
		if(combineOperator_.get_operatorName() == "+")
		{
			return derivatibleFunction1_->secondDerivative(x) + derivatibleFunction2_->secondDerivative(x);
		}
		if(combineOperator_.get_operatorName() == "-")
		{
			return derivatibleFunction1_->secondDerivative(x) - derivatibleFunction2_->secondDerivative(x);
		}
		if(combineOperator_.get_operatorName() == "*")
		{
			return derivatibleFunction1_->secondDerivative(x) * derivatibleFunction2_->func(x)
			    + 2 * derivatibleFunction1_->firstDerivative(x) * derivatibleFunction2_->firstDerivative(x)
				+ derivatibleFunction1_->func(x) * derivatibleFunction2_->secondDerivative(x);
		}
		if(combineOperator_.get_operatorName() == "/")
		{
			double F       =   derivatibleFunction1_->firstDerivative(x) * derivatibleFunction2_->func(x) 
							 - derivatibleFunction1_->func(x) * derivatibleFunction2_->firstDerivative(x);

			double F_prime =   derivatibleFunction1_->secondDerivative(x)*derivatibleFunction2_->func(x) 
				             - derivatibleFunction1_->func(x)*derivatibleFunction2_->secondDerivative(x); 

			double G       =  derivatibleFunction2_->func(x) * derivatibleFunction2_->func(x);
			double G_prime =  2 * derivatibleFunction2_->func(x) * derivatibleFunction2_->firstDerivative(x);

			double numerator   = F_prime*G - F*G_prime;
			double denominator = G*G;
			return numerator/denominator;
		}
		throw("Error: operator not defined!");
	}

	CombinedDerivatibleFunction(const boost::shared_ptr<CombinedDerivatibleFunction>& deriableFunc1, 
								const boost::shared_ptr<CombinedDerivatibleFunction>& deriableFunc2,
								const CombineOperator& combineOperator)
								:derivatibleFunction1_(deriableFunc1),derivatibleFunction2_(deriableFunc2), combineOperator_(combineOperator)
	{}


static const boost::shared_ptr<CombinedDerivatibleFunction> add ( const boost::shared_ptr<CombinedDerivatibleFunction>& combinedDerivableFunc1,
																  const boost::shared_ptr<CombinedDerivatibleFunction>& combinedDerivableFunc2) 
{
	const boost::shared_ptr<CombinedDerivatibleFunction> ptr (new CombinedDerivatibleFunction(combinedDerivableFunc1, 
		combinedDerivableFunc2,
		CombineOperator("+")));
	return ptr;
}

static const boost::shared_ptr<CombinedDerivatibleFunction> sub ( const boost::shared_ptr<CombinedDerivatibleFunction>& combinedDerivableFunc1,
																  const boost::shared_ptr<CombinedDerivatibleFunction>& combinedDerivableFunc2) 
{
	const boost::shared_ptr<CombinedDerivatibleFunction> ptr (new CombinedDerivatibleFunction(combinedDerivableFunc1, 
		combinedDerivableFunc2,
		CombineOperator("-")));
	return ptr;
}


static const boost::shared_ptr<CombinedDerivatibleFunction> mul ( const boost::shared_ptr<CombinedDerivatibleFunction>& combinedDerivableFunc1,
																  const boost::shared_ptr<CombinedDerivatibleFunction>& combinedDerivableFunc2) 
{
	const boost::shared_ptr<CombinedDerivatibleFunction> ptr (new CombinedDerivatibleFunction(combinedDerivableFunc1, 
		combinedDerivableFunc2,
		CombineOperator("*")));
	return ptr;
}


static const boost::shared_ptr<CombinedDerivatibleFunction> div ( const boost::shared_ptr<CombinedDerivatibleFunction>& combinedDerivableFunc1,
																 const boost::shared_ptr<CombinedDerivatibleFunction>& combinedDerivableFunc2) 
{
	const boost::shared_ptr<CombinedDerivatibleFunction> ptr (new CombinedDerivatibleFunction(combinedDerivableFunc1, 
		combinedDerivableFunc2,
		CombineOperator("/")));
	return ptr;
}

//CombinedDerivatibleFunction operator+ (const CombinedDerivatibleFunction& combinedDerivableFunc) 
//{
//	return CombinedDerivatibleFunction(this, 
//		                               &combinedDerivableFunc,
//									   CombineOperator("+"));
//}
};
typedef boost::shared_ptr<CombinedDerivatibleFunction> CombinedDerivatibleFunction_PTR;

class DerivatibleFunction : public CombinedDerivatibleFunction
{
public:

	DerivatibleFunction():CombinedDerivatibleFunction(boost::shared_ptr<CombinedDerivatibleFunction>(), 
													  boost::shared_ptr<CombinedDerivatibleFunction>(),
													  CombineOperator("Non")){} // so you have to implement the func, 1stDev, 2ndDev
};
typedef boost::shared_ptr<CombinedDerivatibleFunction> DerivatibleFunction_PTR;

