#include <cassert>

#include <LMM/instrument/VanillaSwap.h>

namespace LMM
{


	//! Suppose there is a LMM Tenor structure: {T_k}_{k=0}^{N}, and forall k, T_{k+1} - T_k = liborTenor, the unity is in Month. 
	//! a swap begins at: T_i, end at T_j.
	VanillaSwap::VanillaSwap(double strike,
		LMM::Index indexStart, 
		LMM::Index indexEnd, 
		const Tenor& floatingLegTenorType,
		const Tenor& fixedLegTenorType,
		const Tenor& simulationTenorType)
		: strike_(strike)
		, indexStart_(indexStart)
		, indexEnd_(indexEnd)
		, floatingLegTenorType_(floatingLegTenorType)
		, fixedLegTenorType_(fixedLegTenorType)
		, simulationTenorType_(simulationTenorType)
		, floatingVsLiborTenorTypeRatio_( floatingLegTenorType_.ratioTo(simulationTenorType_) )
		, fixedVsLiborTenorTypeRatio_ ( fixedLegTenorType_.ratioTo( simulationTenorType_) )
	{
		assert(floatingLegTenorType == simulationTenorType) ;  

		assert( indexEnd > indexStart ); assert( indexStart >=0 );
		assert( (indexEnd_ - indexStart_)%floatingVsLiborTenorTypeRatio_==0  );
		assert( (indexEnd_ - indexStart_)%fixedVsLiborTenorTypeRatio_   ==0  );
		assert( floatingLegTenorType_ == simulationTenorType_  );         // floatingTenor == lmmTenor

		size_t nbFloatLeg =  (indexEnd_ - indexStart_)/floatingVsLiborTenorTypeRatio_;

		for(size_t i=0; i<nbFloatLeg ; ++i)
		{
			floatingLegPaymentIndexSchedule_.push_back(indexStart_+(i+1)*floatingVsLiborTenorTypeRatio_);
		}

		size_t nbFixedLeg = (indexEnd_ - indexStart_)/fixedVsLiborTenorTypeRatio_;
		for(size_t i=0; i< nbFixedLeg ; ++i)
		{
			fixedLegPaymentIndexSchedule_.push_back(indexStart_+(i+1)*fixedVsLiborTenorTypeRatio_);
		}
	}


	void  VanillaSwap::set_strike(const double& strike) {strike_ = strike;}
	
	const double& VanillaSwap::get_strike() const {return strike_;}

	const Tenor& VanillaSwap::get_fixedLegTenorType()	const { return fixedLegTenorType_     ; }
	
	const Tenor& VanillaSwap::get_floatingLegTenorType()	const { return floatingLegTenorType_  ; }	
	
	const Tenor& VanillaSwap::get_simulationTenorType()  const { return simulationTenorType_   ; }

	size_t VanillaSwap::get_fixedLegTenorLmmTenorRatio() const { return    fixedVsLiborTenorTypeRatio_ ; }
	
	size_t VanillaSwap::get_floatingLegTenorLmmTenorRatio() const { return floatingVsLiborTenorTypeRatio_ ; }		
	
	const std::vector<LMM::Index>& VanillaSwap::get_floatingLegPaymentIndexSchedule() const { return floatingLegPaymentIndexSchedule_; }
	
	const std::vector<LMM::Index>& VanillaSwap::get_fixedLegPaymentIndexSchedule()    const { return fixedLegPaymentIndexSchedule_   ; }

	LMM::Index VanillaSwap::get_indexStart() const {return indexStart_;}
	
	LMM::Index VanillaSwap::get_indexEnd()   const {return indexEnd_  ;}



	void VanillaSwap::write_to_stream(std::ostream& outputstream)const 
	{
		outputstream <<std::endl << "VanillaSwap" <<std::endl;

		outputstream << "strike_="   << strike_ << std::endl;
		outputstream << "indexStart_=" << indexStart_ << std::endl;
		outputstream << "indexEnd_="   << indexEnd_ << std::endl;

		outputstream << "floatingLegTenorType_="  << floatingLegTenorType_ << std::endl;
		outputstream << "fixedLegTenorType_="     << fixedLegTenorType_    << std::endl;
		outputstream << "simulationTenorType_="   << simulationTenorType_  << std::endl;

		outputstream << "floatingPaymentIndexSchedule_{"<<floatingLegPaymentIndexSchedule_[0];
		for(size_t i=1; i<floatingLegPaymentIndexSchedule_.size(); ++i)
		{
			outputstream <<"," << floatingLegPaymentIndexSchedule_[i];
		}outputstream <<"}"<<std::endl;

		outputstream << "fixedLegPaymentIndexSchedule_{"<<fixedLegPaymentIndexSchedule_[0];
		for(size_t i=1; i<fixedLegPaymentIndexSchedule_.size(); ++i)
		{
			outputstream <<","<<fixedLegPaymentIndexSchedule_[i];
		}outputstream <<"}"<<std::endl<<std::endl;
	}


} // end namespace LMM

std::ostream& operator<<(std::ostream& os, const LMM::VanillaSwap& swap){ swap.write_to_stream(os) ; return os; }