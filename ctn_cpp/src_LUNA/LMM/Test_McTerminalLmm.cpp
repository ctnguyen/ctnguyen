#include "HGVolatilityFunction.h"
#include "McGenerator.h"
#include "McTerminalLmm.h"
#include "Correlation.h"
#include "RNGenerator.h"

void test_McTerminalLmm()  // OK: Test passed!
{
	//! LMMTenorStructure
	TenorTypeEnum::TenorTypeEnum tenorType = TenorTypeEnum::TenorTypeEnum::_6M;
	size_t horizonYear = 2;
	LMMTenorStructure lmmTenorStructure(tenorType, horizonYear);
	lmmTenorStructure.print();

	//! volatility function
	double a = -0.06;
	double b = 0.17;
	double c = 0.54;
	double d = 0.17;
	AbcdParams abcdParams(a,b,c,d);
	AbcdPWConstFunction abcdPWConstFunction(abcdParams, lmmTenorStructure);

	VolatilityFunction_PTR hgVolatilityFunction (new HGVolatilityFunction(abcdParams,  lmmTenorStructure)); 
	hgVolatilityFunction->print();

	//! Correlation 1
	size_t nbFactor       = 3; // need to test nbFactor  = 3, and nbFactor = 
	size_t correlFullRank = lmmTenorStructure.get_horizon()+1;
	size_t correlReducedRank = nbFactor;
	CorrelationReductionTyype correlReductionType = CorrelationReductionTyype::PCA;
	double correlAlpha = 0.0;
	double correlBeta  = 0.1;
	Correlation_PTR correlation(new XY_beta_Correlation(correlFullRank,correlReducedRank, correlReductionType,correlAlpha,correlBeta));
	correlation->calculate(); // for print.
	correlation->print();
	////! Correlation 2: don't do reduction.
	//size_t nbFactor          = lmmTenorStructure.get_horizon()+1;; // need to test nbFactor  = 3, and nbFactor = 
	//size_t correlFullRank    = lmmTenorStructure.get_horizon()+1;
	//size_t correlReducedRank = nbFactor;
	//CorrelationReductionTyype correlReductionType = CorrelationReductionTyype::PCA;
	//double correlConst       = 1.0; 
	//Correlation_PTR correlation(new Const_Correlation(correlFullRank,correlReducedRank,correlReductionType,correlConst));


	//! Dispersion
	Dispersion dispersion(correlation, hgVolatilityFunction);


	//McLmm
	double shiftValue = -0.01;
	std::vector<double> shifts(lmmTenorStructure.get_horizon()+1, shiftValue);

	double fwdRate = 0.02;
	std::vector<double> liborsInitValue(lmmTenorStructure.get_horizon()+1, fwdRate);

	unsigned long seed = 47;
	RNGenerator_PTR  rnGenerator(new McGenerator(seed));

	size_t nbSimulation = 1;

	McTerminalLmm mcTerminalLmm(dispersion, shifts, liborsInitValue, rnGenerator, MCSchemeType::MCSchemeType::EULER);

    mcTerminalLmm.print();  // Attention, there are two print: parent class and derived class
}