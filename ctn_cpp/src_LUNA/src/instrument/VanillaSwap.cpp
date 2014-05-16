#include <cassert>

#include <LMM/instrument/VanillaSwap.h>

VanillaSwap::VanillaSwap() 
	: strike_(0.0),
	indexStart_(0),
	indexEnd_(0),
	floatingLegTenorType_(TenorTypeEnum::TenorTypeEnum::_Non),
	fixedLegTenorType_(TenorTypeEnum::TenorTypeEnum::_Non),
	lmmTenorStructureTenorType_(TenorTypeEnum::TenorTypeEnum::_Non)
{}

//! Suppose there is a LMM Tenor structure: {T_k}_{k=0}^{N}, and forall k, T_{k+1} - T_k = liborTenor, the unity is in Month. 
//! a swap begins at: T_i, end at T_j.
VanillaSwap::VanillaSwap(double strike,
	                     Name::indexInLMMTenorStructure  indexStart, 
						 Name::indexInLMMTenorStructure  indexEnd, 
						 TenorTypeEnum::TenorTypeEnum		 floatingLegTenorType, 
						 TenorTypeEnum::TenorTypeEnum		 fixedLegTenorType, 						 
						 TenorTypeEnum::TenorTypeEnum        lmmTenorStructureTenorType)
						 : strike_(strike),
						   indexStart_(indexStart),
						   indexEnd_(indexEnd),
						   floatingLegTenorType_(floatingLegTenorType),
						   fixedLegTenorType_(fixedLegTenorType),
						   lmmTenorStructureTenorType_(lmmTenorStructureTenorType)
{
	//floatingVsLiborTenorTypeRatio_ = get_floatingLegTenorLmmTenorRatio(); //TenorType::TenorTypeRatio(floatingLegTenorType_,lmmTenorStructureTenorType_); 
	fixedVsLiborTenorTypeRatio_    = get_fixedLegTenorLmmTenorRatio();    //TenorType::TenorTypeRatio(fixedLegTenorType_,   lmmTenorStructureTenorType_); 

	assert(TenorTypeEnum::operator==(floatingLegTenorType , lmmTenorStructureTenorType) );

	assert(    indexEnd > indexStart
		    && indexStart >=0
		    && (indexEnd_ - indexStart_)%floatingVsLiborTenorTypeRatio_==0 
		    && (indexEnd_ - indexStart_)%fixedVsLiborTenorTypeRatio_   ==0
			&& TenorTypeEnum::operator==(floatingLegTenorType_ , lmmTenorStructureTenorType_)  );         // floatingTenor == lmmTenor

	size_t floatingPaymentSize =  (indexEnd_ - indexStart_)/floatingVsLiborTenorTypeRatio_;
	size_t fixingPaymentSize   =  (indexEnd_ - indexStart_)/fixedVsLiborTenorTypeRatio_;

	for(size_t i=0; i<floatingPaymentSize; ++i)
	{
		floatingLegPaymentIndexSchedule_.push_back(indexStart_+i+1);
	}

	for(size_t i=0; i<fixingPaymentSize; ++i)
	{
		fixedLegPaymentIndexSchedule_.push_back(indexStart_+(i+1)*fixedVsLiborTenorTypeRatio_);
	}
}

void VanillaSwap::print() const
{

}

void VanillaSwap::print_details() const
{
	std::cout << "indexStart_ = " << indexStart_ << std::endl;
	std::cout << "indexEnd_ = " << indexEnd_ << std::endl;

	std::cout << "floatingPaymentIndexSchedule: " << std::endl;
	for(size_t i=0; i<floatingLegPaymentIndexSchedule_.size(); ++i)
	{
		std::cout << floatingLegPaymentIndexSchedule_[i] << std::endl;
	}

	std::cout << "fixingPaymentIndexSchedule: " << std::endl;
	for(size_t i=0; i<fixedLegPaymentIndexSchedule_.size(); ++i)
	{
		std::cout << fixedLegPaymentIndexSchedule_[i] << std::endl;
	}
}

////! Suppose there is a LMM Tenor structure: {T_k}_{k=0}^{N}, and forall k, T_{k+1} - T_k = liborTenor, the unity is in Month. 
////! a swap begins at: T_i, end at T_j.
//VanillaSwap::VanillaSwap(Name::indexInLMMTenorStructure indexStart,      // i
//						 Name::indexInLMMTenorStructure indexEnd,        // j 
//						 size_t floatingLegfrequency, 
//						 size_t fixedLegfrequency)
//	: strike_(0.),
//	  indexStart_(indexStart),
//	  indexEnd_(indexEnd),
//	  floatingLegfrequency_(floatingLegfrequency), 
//	  fixedLegfrequency_(fixedLegfrequency)
//{
//	size_t floatingPaymentSize =  (indexEnd_ - indexStart_)/floatingLegfrequency_;
//	size_t fixingPaymentSize   =  (indexEnd_ - indexStart_)/fixedLegfrequency_;
//
//	for(size_t i=0; i<floatingPaymentSize; ++i)
//	{
//		floatingPaymentIndexSchedule.push_back(indexStart_+(i+1)*floatingLegfrequency_);
//	}
//
//	for(size_t i=0; i<fixingPaymentSize; ++i)
//	{
//		fixingPaymentIndexSchedule.push_back(indexStart_+(i+1)*fixedLegfrequency_);
//	}
//}