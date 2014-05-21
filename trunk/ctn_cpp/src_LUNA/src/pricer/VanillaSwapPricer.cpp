#include <LMM/pricer/VanillaSwapPricer.h>

void VanillaSwapPricer::precalculate(const LMM::VanillaSwap& vanillaSwap) const
{
	assert(lmmTenorStructure_->get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;
	//! YY TODO: need to implement the == operator for enum TenorType
	assert(lmmTenorStructure_->get_tenorType() == vanillaSwap.get_lmmTenorStructureTenorType());

	//! floatingLeg
	const std::vector<Name::indexInLMMTenorStructure>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	deltaTFloatingLeg_ = std::vector<double>(floatingLegPaymentIndexSchedule.size());
	for(size_t itr = 0; itr<deltaTFloatingLeg_.size(); ++itr)
	{
		size_t index = floatingLegPaymentIndexSchedule[itr];
		deltaTFloatingLeg_[itr] = lmmTenorStructure_->get_deltaT(index-1); // T[index] - T[index-1]

	}	

	//! fixedLeg
	const std::vector<Name::indexInLMMTenorStructure>& fixedLegPaymentIndexSchedule    = vanillaSwap.get_fixedLegPaymentIndexSchedule();
	fixedLegTenorLmmTenorRatio_    = vanillaSwap.get_fixedLegTenorLmmTenorRatio();  
	deltaTFixedLeg_    = std::vector<double>(fixedLegPaymentIndexSchedule.size());
	for(size_t itr = 0; itr<deltaTFixedLeg_.size(); ++itr)
	{
		size_t index = fixedLegPaymentIndexSchedule[itr];
		double t2 = lmmTenorStructure_->get_tenorDate(index);
		double t1 = lmmTenorStructure_->get_tenorDate(index-fixedLegTenorLmmTenorRatio_);
		deltaTFixedLeg_[itr] = t2-t1;
	}
}



double VanillaSwapPricer::annuity( Name::indexInLMMTenorStructure indexValuationDate,
								   const LMM::VanillaSwap& vanillaSwap,
								   const std::vector<double>& numeraire) const
{
	assert(indexValuationDate <= vanillaSwap.get_indexStart()); //YY TODO: this test too slow, esp: within MC simulation
	assert(lmmTenorStructure_->get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;

	double price = 0.0;
	const std::vector<Name::indexInLMMTenorStructure>& fixedLegPaymentIndexSchedule  = vanillaSwap.get_fixedLegPaymentIndexSchedule();
	for(size_t itr = 0; itr < fixedLegPaymentIndexSchedule.size(); ++itr)
	{
		size_t fixedLegPaymentIndex = fixedLegPaymentIndexSchedule[itr]; // = i+1
		double delta_T              = deltaTFixedLeg_[itr];
		//std::cout << "numeraire[indexValuationDate]/numeraire[fixedLegPaymentIndex] = " << numeraire[indexValuationDate]/numeraire[fixedLegPaymentIndex] << std::endl;
		price			           += delta_T*numeraire[indexValuationDate]/numeraire[fixedLegPaymentIndex];		
	}
	return price;
}

double VanillaSwapPricer::pvFixedLeg(Name::indexInLMMTenorStructure indexValuationDate,
								     const LMM::VanillaSwap& vanillaSwap,
									 const std::vector<double>& numeraire)  const
{
	assert(indexValuationDate <= vanillaSwap.get_indexStart()); //YY TODO: this test too slow, esp: within MC simulation
	assert(lmmTenorStructure_->get_horizon() >= vanillaSwap.get_indexEnd());  // if not cannot price this swap;

	return vanillaSwap.get_strike()*annuity(indexValuationDate,vanillaSwap,numeraire);
}


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
	const std::vector<Name::indexInLMMTenorStructure>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//size_t floatingLegTenorLmmTenorRatio = vanillaSwap.get_floatingLegTenorLmmTenorRatio();
	Name::indexInLMMTenorStructure indexFloatingLegStart = floatingLegPaymentIndexSchedule.front();
	Name::indexInLMMTenorStructure indexFloatingLegEnd   = floatingLegPaymentIndexSchedule.back();
	double pvFloatingLeg =  ZC[indexFloatingLegStart-1] - ZC[indexFloatingLegEnd];


	////! pvFloatingLeg: exact
	//double pvFloatingLeg = 0.0;
	//const std::vector<Name::indexInLMMTenorStructure>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//for(size_t itr = 0; itr < floatingLegPaymentIndexSchedule.size(); ++itr)
	//{
	//	//! At time T_{i+1}, pay: L_i(T_i)
	//	size_t floatingLegPaymentIndex = floatingLegPaymentIndexSchedule[itr]; // = i+1
	//	size_t indexLibor			   = floatingLegPaymentIndex-1; // =i, because : floatingTenor = lmmTenor  
	//	pvFloatingLeg				  += floatingLegdelta_T*initLibor[indexLibor]*ZC[floatingLegPaymentIndex];		
	//}


	//! pvFixedLeg
	double pvFixedLeg = 0.0;
	const std::vector<Name::indexInLMMTenorStructure>& fixedLegPaymentIndexSchedule  = vanillaSwap.get_fixedLegPaymentIndexSchedule();
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
	std::vector<double> numeraire(horizon+2); // determinisitc IR
	for(size_t i=1; i<ZC.size(); ++i)
	{
		numeraire[i] = 1.0/ZC[i];
	}

	//! pvFloatingLeg: 1 - 1
	const std::vector<Name::indexInLMMTenorStructure>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//size_t floatingLegTenorLmmTenorRatio = vanillaSwap.get_floatingLegTenorLmmTenorRatio();
	Name::indexInLMMTenorStructure indexFloatingLegStart = floatingLegPaymentIndexSchedule.front();
	Name::indexInLMMTenorStructure indexFloatingLegEnd   = floatingLegPaymentIndexSchedule.back();
	double pvFloatingLegValue =  ZC[indexFloatingLegStart-1] - ZC[indexFloatingLegEnd];


	////! pvFloatingLeg: exact
	//double pvFloatingLeg = 0.0;
	//const std::vector<Name::indexInLMMTenorStructure>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//for(size_t itr = 0; itr < floatingLegPaymentIndexSchedule.size(); ++itr)
	//{
	//	//! At time T_{i+1}, pay: L_i(T_i)
	//	size_t floatingLegPaymentIndex = floatingLegPaymentIndexSchedule[itr]; // = i+1
	//	size_t indexLibor			   = floatingLegPaymentIndex-1; // =i, because : floatingTenor = lmmTenor  
	//	pvFloatingLeg				  += floatingLegdelta_T*initLibor[indexLibor]*ZC[floatingLegPaymentIndex];		
	//}


	Name::indexInLMMTenorStructure indexValuationDate = 0;
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
	std::vector<double> numeraire(horizon+2); // determinisitc IR
	for(size_t i=1; i<ZC.size(); ++i)
	{
		numeraire[i] = 1.0/ZC[i];
	}

	//! pvFloatingLeg: 1 - 1
	const std::vector<Name::indexInLMMTenorStructure>& floatingLegPaymentIndexSchedule = vanillaSwap.get_floatingLegPaymentIndexSchedule();
	//size_t floatingLegTenorLmmTenorRatio = vanillaSwap.get_floatingLegTenorLmmTenorRatio();
	Name::indexInLMMTenorStructure indexFloatingLegStart = floatingLegPaymentIndexSchedule.front();
	Name::indexInLMMTenorStructure indexFloatingLegEnd   = floatingLegPaymentIndexSchedule.back();
	double pvFloatingLegValue =  ZC[indexFloatingLegStart-1] - ZC[indexFloatingLegEnd];

	//! pvFixingLeg
	Name::indexInLMMTenorStructure indexValuationDate = 0;
	double pvFixedLegValue = pvFixedLeg(indexValuationDate,vanillaSwap,numeraire);
	return pvFloatingLegValue / pvFixedLegValue;
}
