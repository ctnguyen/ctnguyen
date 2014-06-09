#include <LMM/pricer/VanillaSwapPricer.h>


VanillaSwapPricer::VanillaSwapPricer(LMMTenorStructure_PTR lmmTenorStructure)	: lmmTenorStructure_(lmmTenorStructure){};

VanillaSwapPricer::~VanillaSwapPricer()
{}

double VanillaSwapPricer::swapNPV_Analytical_1(const LMM::VanillaSwap& vanillaSwap, const std::vector<double>& liborsInitValue)  const // initLibor[i] = L_i[T_0]
{
	assert(lmmTenorStructure_->get_horizon()+1 == liborsInitValue.size());
	assert(lmmTenorStructure_->get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;
	size_t horizon = lmmTenorStructure_->get_horizon();


	double floatingLegdelta_T = vanillaSwap.get_floatingLegTenorType().convertToYear();
	double fixedLegdelta_T = vanillaSwap.get_fixedLegTenorType().convertToYear();

	//! ZC[i] = P(T_0,T_i)
	std::vector<double> ZC(horizon+2);
	ZC[0] = 1.0;
	for(size_t i=1; i<ZC.size(); ++i)
	{
		ZC[i] = ZC[i-1]/(1+floatingLegdelta_T*liborsInitValue[i-1]);
	}

	//! pvFloatingLeg: 1 - 1
	const std::vector<LMM::Index>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//size_t floatingLegTenorLmmTenorRatio = vanillaSwap.get_floatingLegTenorLmmTenorRatio();
	LMM::Index indexFloatingLegStart = floatingLegPaymentIndexSchedule.front();
	LMM::Index indexFloatingLegEnd   = floatingLegPaymentIndexSchedule.back();
	double pvFloatingLeg =  ZC[indexFloatingLegStart-1] - ZC[indexFloatingLegEnd];


	////! pvFloatingLeg: exact
	//double pvFloatingLeg = 0.0;
	//const std::vector<LMM::Index>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//for(size_t itr = 0; itr < floatingLegPaymentIndexSchedule.size(); ++itr)
	//{
	//	//! At time T_{i+1}, pay: L_i(T_i)
	//	size_t floatingLegPaymentIndex = floatingLegPaymentIndexSchedule[itr]; // = i+1
	//	size_t indexLibor			   = floatingLegPaymentIndex-1; // =i, because : floatingTenor = lmmTenor  
	//	pvFloatingLeg				  += floatingLegdelta_T*initLibor[indexLibor]*ZC[floatingLegPaymentIndex];		
	//}


	//! pvFixedLeg
	double pvFixedLeg = 0.0;
	const std::vector<LMM::Index>& fixedLegPaymentIndexSchedule  = vanillaSwap.get_fixedLegPaymentIndexSchedule();
	for(size_t itr = 0; itr < fixedLegPaymentIndexSchedule.size(); ++itr)
	{
		size_t fixedLegPaymentIndex = fixedLegPaymentIndexSchedule[itr]; // = i+1
		pvFixedLeg 		    	   += fixedLegdelta_T*ZC[fixedLegPaymentIndex];		
	}
	pvFixedLeg *= vanillaSwap.get_strike();

	return pvFloatingLeg - pvFixedLeg;
}

double VanillaSwapPricer::swapNPV_Analytical_2(const LMM::VanillaSwap& vanillaSwap, const std::vector<double>& liborsInitValue)  const // initLibor[i] = L_i[T_0]
{
	assert(lmmTenorStructure_->get_horizon()+1 == liborsInitValue.size());
	assert(lmmTenorStructure_->get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;
	size_t horizon = lmmTenorStructure_->get_horizon();


	double floatingLegdelta_T = vanillaSwap.get_floatingLegTenorType().convertToYear();
	double fixedLegdelta_T = vanillaSwap.get_fixedLegTenorType().convertToYear();

	//! ZC[i] = P(T_0,T_i)
	std::vector<double> ZC(horizon+2);
	ZC[0] = 1.0;
	for(size_t i=1; i<ZC.size(); ++i)
	{
		ZC[i] = ZC[i-1]/(1+floatingLegdelta_T*liborsInitValue[i-1]);
	}

	//! numeraire
	std::vector<double> numeraire(ZC.size() ); // determinisitc IR
	for(size_t i=0; i<ZC.size(); ++i)
	{
		numeraire[i] = 1.0/ZC[i];
	}

	//! pvFloatingLeg: 1 - 1
	const std::vector<LMM::Index>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//size_t floatingLegTenorLmmTenorRatio = vanillaSwap.get_floatingLegTenorLmmTenorRatio();
	LMM::Index indexFloatingLegStart = floatingLegPaymentIndexSchedule.front();
	LMM::Index indexFloatingLegEnd   = floatingLegPaymentIndexSchedule.back();
	double pvFloatingLegValue =  ZC[indexFloatingLegStart-1] - ZC[indexFloatingLegEnd];


	////! pvFloatingLeg: exact
	//double pvFloatingLeg = 0.0;
	//const std::vector<LMM::Index>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//for(size_t itr = 0; itr < floatingLegPaymentIndexSchedule.size(); ++itr)
	//{
	//	//! At time T_{i+1}, pay: L_i(T_i)
	//	size_t floatingLegPaymentIndex = floatingLegPaymentIndexSchedule[itr]; // = i+1
	//	size_t indexLibor			   = floatingLegPaymentIndex-1; // =i, because : floatingTenor = lmmTenor  
	//	pvFloatingLeg				  += floatingLegdelta_T*initLibor[indexLibor]*ZC[floatingLegPaymentIndex];		
	//}


	LMM::Index indexValuationDate = 0;
	double pvFixedLegValue = pvFixedLeg(indexValuationDate,vanillaSwap,numeraire);
	return pvFloatingLegValue - pvFixedLegValue;
}

//! same as swapNPV_Analytical_1(...)
double VanillaSwapPricer::swapRate_Analytical(const LMM::VanillaSwap& vanillaSwap,
											  const std::vector<double>& liborsInitValue)  const
{
	assert(lmmTenorStructure_->get_horizon()+1 == liborsInitValue.size());
	assert(lmmTenorStructure_->get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;
	size_t horizon = lmmTenorStructure_->get_horizon();
	
	const double fixedLegdelta_T = vanillaSwap.get_fixedLegTenorType().convertToYear();
	const double floatingLegdelta_T = vanillaSwap.get_floatingLegTenorType().convertToYear();
	
	//! ZC[i] = P(T_0,T_i)
	std::vector<double> ZC(horizon+2);
	ZC[0] = 1.0;
	for(size_t i=1; i<ZC.size(); ++i)
	{
		ZC[i] = ZC[i-1]/(1+floatingLegdelta_T*liborsInitValue[i-1]);
	}

	//! numeraire
	std::vector<double> numeraire( ZC.size() ); // determinisitc IR
	for(size_t i=0; i<ZC.size(); ++i)
	{
		numeraire[i] = 1.0/ZC[i];
	}

	//! pvFloatingLeg: 1 - 1
	const std::vector<LMM::Index>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//size_t floatingLegTenorLmmTenorRatio = vanillaSwap.get_floatingLegTenorLmmTenorRatio();
	LMM::Index indexFloatingLegStart = floatingLegPaymentIndexSchedule.front();
	LMM::Index indexFloatingLegEnd   = floatingLegPaymentIndexSchedule.back();
	double pvFloatingLegValue =  ZC[indexFloatingLegStart-1] - ZC[indexFloatingLegEnd];

	//! pvAnnuity
	LMM::Index indexValuationDate = 0;
	double pvAnnuity = annuity(indexValuationDate,vanillaSwap,numeraire);
	return pvFloatingLegValue / pvAnnuity;
}



double VanillaSwapPricer::annuity( 
	const LMM::Index            indexValuationDate,
	const LMM::VanillaSwap    & vanillaSwap,
	const std::vector<double> & numeraire) const
{
	assert(indexValuationDate <= vanillaSwap.get_indexStart()); //YY TODO: this test too slow, esp: within MC simulation
	assert(lmmTenorStructure_->get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;

	double price = 0.0;
	const std::vector<LMM::Index>& fixedLegPaymentIndexSchedule  = vanillaSwap.get_fixedLegPaymentIndexSchedule();
	for(size_t itr = 0; itr < fixedLegPaymentIndexSchedule.size(); ++itr)
	{
		size_t fixedLegPaymentIndex = fixedLegPaymentIndexSchedule[itr]; // = i+1
		const std::vector<double>& deltaTFixedLeg_ = vanillaSwap.get_DeltaTFixedLeg();
		const double& delta_T              = deltaTFixedLeg_[itr];
		//std::cout << "numeraire[indexValuationDate]/numeraire[fixedLegPaymentIndex] = " << numeraire[indexValuationDate]/numeraire[fixedLegPaymentIndex] << std::endl;
		price			           += delta_T*numeraire[indexValuationDate]/numeraire[fixedLegPaymentIndex];		
	}
	return price;
}

double VanillaSwapPricer::forwardSwapRate( 
	const LMM::Index            indexValuationDate,
	const LMM::VanillaSwap    & vanillaSwap,
	const std::vector<double> & numeraire) const
{
	/*
	// see Damiano Brigo 2006 p238
	const size_t T_alpha = vanillaSwap.get_indexStart();
	const size_t T_beta = vanillaSwap.get_indexEnd();

	assert(indexValuationDate <= T_alpha); 
	assert(lmmTenorStructure_->get_horizon() >= T_beta);  
		 
	const std::vector<LMM::Index>& fixedLegPaymentIndexSchedule  = vanillaSwap.get_fixedLegPaymentIndexSchedule();

	const double C_alpha_beta = this->annuity(indexValuationDate,vanillaSwap,numeraire);
	const size_t alphaIndex = indexValuationDate;
	const size_t betaIndex = fixedLegPaymentIndexSchedule.back();
	const double P_t_alpha = 1.0/ numeraire[alphaIndex];
	const double P_t_beta  = 1.0/ numeraire[betaIndex];

	double S_alpha_beta = (P_t_alpha - P_t_beta) / C_alpha_beta;

	return S_alpha_beta;
	*/
	return 0.0;
}

double VanillaSwapPricer::pvFixedLeg(
	const LMM::Index            indexValuationDate,
	const LMM::VanillaSwap    & vanillaSwap,
	const std::vector<double> & numeraire)  const
{
	assert(indexValuationDate <= vanillaSwap.get_indexStart()); //YY TODO: this test too slow, esp: within MC simulation
	assert(lmmTenorStructure_->get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;
	const double calculatedAnuity = this->annuity(indexValuationDate,vanillaSwap,numeraire);
	return vanillaSwap.get_strike()*calculatedAnuity;
}
