#include <iostream>

#include <LMM/Name.h>
#include <LMM/helper/Printer.h>
#include <LMM/helper/McGenerator.h>
#include <LMM/instrument/VanillaSwap.h>
#include <LMM/ModelMCLMM/HGVolatilityFunction.h>
#include <LMM/ModelMCLMM/McTerminalLmm.h>
#include <LMM/ModelMCLMM/McSpotLmm.h>
#include <LMM/pricer/MCLmmVanillaSwapPricer.h>


//----------------------------------------------------------------------------------------------
//
//                                       Test_VanillaSwap
//
//----------------------------------------------------------------------------------------------
VanillaSwap get_VanillaSwap()
{
	double strike = 0.04;
	Name::indexInLMMTenorStructure  indexStart = 12; // 12
	Name::indexInLMMTenorStructure  indexEnd   = 18; // 28;
	TenorTypeEnum::TenorTypeEnum	floatingLegTenorType = TenorTypeEnum::TenorTypeEnum::_6M;
	TenorTypeEnum::TenorTypeEnum	fixedLegTenorType    = TenorTypeEnum::TenorTypeEnum::_1Y; 						 
	TenorTypeEnum::TenorTypeEnum    lmmTenorStructureTenorType = TenorTypeEnum::TenorTypeEnum::_6M;

	VanillaSwap vanillaSwap(strike, indexStart, indexEnd, floatingLegTenorType, fixedLegTenorType, lmmTenorStructureTenorType);
	return vanillaSwap;
}

void test_VanillaSwap()
{
	VanillaSwap vanillaSwap = get_VanillaSwap();
	vanillaSwap.print_details();
}



//----------------------------------------------------------------------------------------------
//
//                                       Test_VanillaSwapPricer
//
//----------------------------------------------------------------------------------------------
MCLmm_PTR get_McLmm(bool TerminalOrSpotProb, MCSchemeType::MCSchemeType mcSchemeType, std::vector<double>& liborsInitValue_op)
{
//! McTerminalLmm
	//! LMMTenorStructure
	TenorTypeEnum::TenorTypeEnum tenorType = TenorTypeEnum::TenorTypeEnum::_6M;
	size_t horizonYear = 15;
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
	double correlBeta  = 0.04;
	Correlation_PTR correlation(new XY_beta_Correlation(correlFullRank,correlReducedRank, correlReductionType,correlAlpha,correlBeta));
	correlation->calculate(); // for print.
	correlation->print();

	//! Dispersion
	Dispersion dispersion(correlation, hgVolatilityFunction);

	//McLmm
	double shiftValue = 0.0; // -0.01;
	std::vector<double> shifts(lmmTenorStructure.get_horizon()+1, shiftValue);

	double fwdRate = 0.1;
	std::vector<double> liborsInitValue(lmmTenorStructure.get_horizon()+1, fwdRate);
	liborsInitValue_op = liborsInitValue;

	unsigned long seed = 47;
	RNGenerator_PTR  rnGenerator(new McGenerator(seed));

	if(TerminalOrSpotProb)
	{
		MCLmm_PTR mclmm(new McTerminalLmm (dispersion, shifts, liborsInitValue, rnGenerator, mcSchemeType));
		return mclmm;
	}
	else
	{
		MCLmm_PTR mclmm(new McSpotLmm (dispersion, shifts, liborsInitValue, rnGenerator, mcSchemeType));
		return mclmm;
	}
	
}

void test_McLmm( bool TerminalOrSpotProb, 
	            MCSchemeType::MCSchemeType mcSchemeType,
				size_t minNbSimulation, 
				size_t maxNbSimulation,
				double bnSimualtionPowStep,
				//! output
				std::vector<size_t>& nbSimulationVector,  // output
				std::vector<double>& swapNPVResultVector, // output
				double& analyticalSwapPrice)              // output
{
	VanillaSwap vanillaSwap = get_VanillaSwap();
	std::vector<double> liborsInitValue;
	MCLmm_PTR mclmm = get_McLmm(TerminalOrSpotProb, mcSchemeType,liborsInitValue);

	MCLmmVanillaSwapPricer mcLmmVanillaSwapPricer(mclmm);

	//std::vector<size_t> nbSimulationVector;
	//std::vector<double> swapNPVResultVector;
	nbSimulationVector.clear();
	swapNPVResultVector.clear();

	for(size_t i=0;; ++i)
	{
		size_t nbSimulation = (size_t)std::pow(bnSimualtionPowStep,i)*minNbSimulation;
		if(nbSimulation>maxNbSimulation)
			break;
		nbSimulationVector.push_back(nbSimulation);
		swapNPVResultVector.push_back(mcLmmVanillaSwapPricer.swapNPV(vanillaSwap, nbSimulation));
		mcLmmVanillaSwapPricer.resetGeneratorToinitSeed(); // for the next generation begin with the same seed as this one...
	}

	analyticalSwapPrice = mcLmmVanillaSwapPricer.swapNPV_Analytical_1(vanillaSwap,liborsInitValue);
}



void test_VanillaSwapPricer()
{
	size_t minNbSimulation = 100;
	size_t maxNbSimulation = 300000; //300000;
	double bnSimualtionPowStep = 2;

	std::vector<size_t> nbSimulationVector;
	std::vector<double> swapNPVResultVector;
	double analyticalSwapPrice=0.0;

	std::string fileName = "test_VanillaSwapPricer.csv"; //+ MCSchemeType::mcSchemeType2String(mcSchemeType) +".csv";
	std::string path = printPath + fileName;

	//! Terminal Euler
	test_McLmm( true, MCSchemeType::MCSchemeType::EULER,minNbSimulation,maxNbSimulation,bnSimualtionPowStep,
		nbSimulationVector, swapNPVResultVector, analyticalSwapPrice);
	std::vector<double> analyticalSwapPriceConstVector(nbSimulationVector.size(), analyticalSwapPrice);

	std::cout << analyticalSwapPrice << std::endl;
	
	PrintElement_PTR nbSimulationVector_print   = PrintElement_PTR(new VectorPrintElement<std::vector<size_t>>("nbSimulationVector", nbSimulationVector));
	PrintElement_PTR analyticalSwapPrice_print  = PrintElement_PTR(new VectorPrintElement<std::vector<double>>("analyticalSwapPrice", analyticalSwapPriceConstVector));
	PrintElement_PTR Euler_swapNPVResultVector_print  = PrintElement_PTR(new VectorPrintElement<std::vector<double>>("Euler_swapNPVResultVector", swapNPVResultVector));

	//! Terminal PC
	test_McLmm( true, MCSchemeType::MCSchemeType::PC,minNbSimulation,maxNbSimulation,bnSimualtionPowStep,
				nbSimulationVector,swapNPVResultVector, analyticalSwapPrice);
	PrintElement_PTR PC_swapNPVResultVector_print  = PrintElement_PTR(new VectorPrintElement<std::vector<double>>("PC_swapNPVResultVector", swapNPVResultVector));


	//! Terminal IPC
	test_McLmm( true, MCSchemeType::MCSchemeType::IPC,minNbSimulation,maxNbSimulation,bnSimualtionPowStep,
				nbSimulationVector,swapNPVResultVector, analyticalSwapPrice);
	PrintElement_PTR IPC_swapNPVResultVector_print  = PrintElement_PTR(new VectorPrintElement<std::vector<double>>("IPC_swapNPVResultVector", swapNPVResultVector));


	//! Spot Euler
	test_McLmm( false, MCSchemeType::MCSchemeType::EULER,minNbSimulation,maxNbSimulation,bnSimualtionPowStep,
		nbSimulationVector,swapNPVResultVector, analyticalSwapPrice);
	PrintElement_PTR Spot_EULER_swapNPVResultVector_print  = PrintElement_PTR(new VectorPrintElement<std::vector<double>>("Spot_EULER_swapNPVResultVector_print", swapNPVResultVector));

	//! Spot PC
	test_McLmm( false, MCSchemeType::MCSchemeType::PC,minNbSimulation,maxNbSimulation,bnSimualtionPowStep,
		nbSimulationVector,swapNPVResultVector, analyticalSwapPrice);
	PrintElement_PTR Spot_PC_swapNPVResultVector_print  = PrintElement_PTR(new VectorPrintElement<std::vector<double>>("Spot_PC_swapNPVResultVector_print", swapNPVResultVector));


	std::vector<PrintElement_PTR> elements_print;
	elements_print.push_back(nbSimulationVector_print);
	elements_print.push_back(analyticalSwapPrice_print);
	elements_print.push_back(Euler_swapNPVResultVector_print);
	elements_print.push_back(PC_swapNPVResultVector_print);
	elements_print.push_back(IPC_swapNPVResultVector_print);
	elements_print.push_back(Spot_EULER_swapNPVResultVector_print);
	elements_print.push_back(Spot_PC_swapNPVResultVector_print);


	Printer printer(path, elements_print);
	printer.print();
}