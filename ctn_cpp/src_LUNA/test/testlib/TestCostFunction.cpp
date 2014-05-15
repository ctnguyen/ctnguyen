//#include "TestCostFunction.h"
//#include <cassert>
//TestCostFunction::TestCostFunction(double a, double b, double c)
//	: a_(a),b_(b),c_(c)
//{}
//
//TestCostFunction::~TestCostFunction() {}
//
//Real TestCostFunction::value(const Array & x) const 
//{
//	return a_ + b_*x[0] + c_*x[0]*x[0];
//}
//
//Disposable<Array> TestCostFunction::values(const Array& x) const 
//{
//	//QL_REQUIRE (x. size ()==1, "x is a one dimension variable");
//	assert(x.size ()==1);
//	Array res(1);
//	res[0] = value(x);
//	return res;
//}
//
//double TestCostFunction::get_a() const {return a_;}
//double TestCostFunction::get_b() const {return b_;}
//double TestCostFunction::get_c() const {return c_;}