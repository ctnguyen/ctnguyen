
#include <test/testlib/Test.h>
int main()
{

	//! Caplet Test
	//pricingCapletTest();

	//! Swaption Test
	//pricingSwaptionTest();

	//DateCreator::testMatrixDatesCreator();

	//! YY Test: test MC Euler 
	
	//test_VanillaSwap();
	//test_VanillaSwapPricer();
	
	test_VanillaSwaptionPricer();
	
	//test_DateConvention();

	test_InegrationMethod();

	test_DerivatibleFunction();

	test_BlackGreek();

	return 1;
}

