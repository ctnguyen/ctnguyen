#include <cassert>

#include <LMM/instrument/VanillaSwap.h>

namespace LMM
{


	//! Suppose there is a LMM Tenor structure: {T_k}_{k=0}^{N}, and forall k, T_{k+1} - T_k = liborTenor, the unity is in Month. 
	//! a swap begins at: T_i, end at T_j.
	VanillaSwap::VanillaSwap(const double& strike,
		LMM::Index indexStart, 
		LMM::Index indexEnd, 
		const Tenor& floatingLegTenorType,
		const Tenor& fixedLegTenorType,
		LMMTenorStructure_PTR simulationStructure)
		: strike_(strike)
		, indexStart_(indexStart)
		, indexEnd_(indexEnd)
		, floatingLegTenorType_(floatingLegTenorType)
		, fixedLegTenorType_(fixedLegTenorType)
		, simulationStructure_(simulationStructure)
		, floatingVsLiborTenorTypeRatio_( floatingLegTenorType_.ratioTo(simulationStructure_->get_tenorType() ) )
		, fixedVsLiborTenorTypeRatio_ ( fixedLegTenorType_.ratioTo( simulationStructure_->get_tenorType() ) )
	{
		assert(floatingLegTenorType == simulationStructure_->get_tenorType() ) ;  

		assert( indexEnd > indexStart ); assert( indexStart >=0 );
		assert( (indexEnd_ - indexStart_)%floatingVsLiborTenorTypeRatio_==0  );
		assert( (indexEnd_ - indexStart_)%fixedVsLiborTenorTypeRatio_   ==0  );
		assert( floatingLegTenorType_ == simulationStructure_->get_tenorType() );         // floatingTenor == lmmTenor

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

		//precalculate deltaT for fixed and float legs, moved from VanillaSwapPricer (30.05.2014)
		assert( simulationStructure_->get_horizon()   >= this->get_indexEnd()            );  // if not cannot price this swap;
		assert( simulationStructure_->get_tenorType() == this->get_simulationTenorType() );

		//! floatingLeg
		const std::vector<LMM::Index>& floatingLegPaymentIndexSchedule = this->get_floatingLegPaymentIndexSchedule();
		deltaTFloatingLeg_.resize( floatingLegPaymentIndexSchedule.size() );
		for(size_t itr = 0; itr<deltaTFloatingLeg_.size(); ++itr)
		{
			size_t index = floatingLegPaymentIndexSchedule[itr];
			deltaTFloatingLeg_[itr] = simulationStructure_->get_deltaT(index-1); // T[index] - T[index-1]

		}	

		//! fixedLeg
		const std::vector<LMM::Index>& fixedLegPaymentIndexSchedule    = this->get_fixedLegPaymentIndexSchedule();
		deltaTFixedLeg_.resize(fixedLegPaymentIndexSchedule.size());
		for(size_t itr = 0; itr<deltaTFixedLeg_.size(); ++itr)
		{
			size_t index = fixedLegPaymentIndexSchedule[itr];
			double t2 = simulationStructure_->get_tenorDate(index);
			double t1 = simulationStructure_->get_tenorDate(index - this->get_fixedLegTenorLmmTenorRatio() );
			deltaTFixedLeg_[itr] = t2-t1;
		}
	}


	void  VanillaSwap::set_strike(const double& strike) {strike_ = strike;}

	const double& VanillaSwap::get_strike() const {return strike_;}

	const Tenor& VanillaSwap::get_fixedLegTenorType()	const { return fixedLegTenorType_     ; }

	const Tenor& VanillaSwap::get_floatingLegTenorType()	const { return floatingLegTenorType_  ; }	

	const Tenor& VanillaSwap::get_simulationTenorType()  const { return simulationStructure_->get_tenorType() ; }

	LMMTenorStructure_PTR VanillaSwap::get_LMMTenorStructure()  const { return simulationStructure_; }

	size_t VanillaSwap::get_fixedLegTenorLmmTenorRatio() const { return    fixedVsLiborTenorTypeRatio_ ; }

	size_t VanillaSwap::get_floatingLegTenorLmmTenorRatio() const { return floatingVsLiborTenorTypeRatio_ ; }		

	const std::vector<LMM::Index>& VanillaSwap::get_floatingLegPaymentIndexSchedule() const { return floatingLegPaymentIndexSchedule_; }

	const std::vector<LMM::Index>& VanillaSwap::get_fixedLegPaymentIndexSchedule()    const { return fixedLegPaymentIndexSchedule_   ; }

	const std::vector<double>& VanillaSwap::get_DeltaTFloatLeg() const { return deltaTFloatingLeg_ ; }
	const std::vector<double>& VanillaSwap::get_DeltaTFixedLeg() const { return deltaTFixedLeg_    ; }


	LMM::Index VanillaSwap::get_indexStart() const {return indexStart_;}

	LMM::Index VanillaSwap::get_indexEnd()   const {return indexEnd_  ;}



	void VanillaSwap::write_to_stream(std::ostream& outputstream)const 
	{
		outputstream  << "VanillaSwap" <<std::endl<<std::endl;

		outputstream << strike_     << ";strike_ ; "     << std::endl;
		outputstream << indexStart_ << ";indexStart_ ; " << std::endl;
		outputstream << indexEnd_   << ";indexEnd_ ; "   << std::endl;

		outputstream << floatingLegTenorType_                 << ";floatingLegTenorType_ ;" << std::endl;
		outputstream << fixedLegTenorType_                    << ";fixedLegTenorType_ ; "   << std::endl;
		outputstream << simulationStructure_->get_tenorType() << ";simulationTenorType_ ; " << std::endl<< std::endl<< std::endl;

		outputstream << ";;;"<<std::endl;
		for(size_t i=0; i<floatingLegPaymentIndexSchedule_.size(); ++i)
		{
			outputstream << floatingLegPaymentIndexSchedule_[i] <<";" ;
		}outputstream << ";floatingPaymentIndexSchedule_ ; "<<std::endl;

		
		outputstream << ";;;"<<std::endl;
		for(size_t i=0; i<fixedLegPaymentIndexSchedule_.size(); ++i)
		{
			outputstream <<fixedLegPaymentIndexSchedule_[i]<<";";
		}outputstream << ";fixedLegPaymentIndexSchedule_ ; "<<std::endl;
		
		
		outputstream << ";;;"<<std::endl;
		for(size_t i=0; i<deltaTFloatingLeg_.size(); ++i)
		{
			outputstream << deltaTFloatingLeg_[i]<<";" ;
		}outputstream << ";deltaTFloatingLeg_ ;"<<std::endl;

		
		outputstream << ";;;"<<std::endl;
		for(size_t i=0; i<deltaTFixedLeg_.size(); ++i)
		{
			outputstream <<deltaTFixedLeg_[i]<<";";
		}outputstream << ";deltaTFixedLeg_ ;"<<std::endl;
	}
} // end namespace LMM

std::ostream& operator<<(std::ostream& os, const LMM::VanillaSwap& swap){ swap.write_to_stream(os) ; return os; }