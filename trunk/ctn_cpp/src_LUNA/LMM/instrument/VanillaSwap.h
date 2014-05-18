
#pragma once
#include <vector>
#include <string>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

#include <LMM/Name.h>
#include <LMM/instrument/TenorType.h>

//YY  Now suppose we use the LMM model Tenor, to change it latter. 
// 1. suppose knowing the LMM's Tenor structure. 
// 2. Suppose fixing / floating leg start and end at the same date;  ---- checked
// 3. Suppose floatingTenor = LMM discretization tenor.              ---- not checked.


//! Suppose there is a LMM Tenor structure: {T_k}_{k=0}^{N}, and forall k, T_{k+1} - T_k = liborTenor, the unity is in Month. 
//! a swap begins at: T_i, end at T_j.

namespace LMM
{

class VanillaSwap
{
private:
	double strike_;

	Name::indexInLMMTenorStructure indexStart_;       // i 
	Name::indexInLMMTenorStructure indexEnd_;         // j 

	Tenor floatingLegTenorType_;			  // floatingLeg payment frequency = Libor's tenorType
	Tenor fixedLegTenorType_;			  // fixedLeg payment frequency: each "1M", "3M", "6M", "1Y"
	Tenor lmmTenorStructureTenorType_;     // fixedLeg payment frequency: each "1M", "3M", "6M", "1Y"

	size_t floatingVsLiborTenorTypeRatio_;
	size_t fixedVsLiborTenorTypeRatio_;


	//size_t floatingLegfrequency_; //!  floatingLeg pays at: indexStart_ + (k+1)*floatingVsLiborTenorTypeRatio_,     k=0,1,2, ...
	//size_t fixedLegfrequency_;    //!  fixedLeg    pays at: indexStart_ + (k+1)*fixedVsLiborTenorTypeRatio_, k=0,1,2, ...
	std::vector<Name::indexInLMMTenorStructure> floatingLegPaymentIndexSchedule_; // give index in LMMTenorStructure 
	std::vector<Name::indexInLMMTenorStructure> floatingLegLiborIndex_;           // liborIndex correspond to the paymentdate: if MCLMM use the same lmmTenorStrucutre to do simulation
	std::vector<Name::indexInLMMTenorStructure> fixedLegPaymentIndexSchedule_;    

public:
	VanillaSwap();

	VanillaSwap(double strike,
		Name::indexInLMMTenorStructure  indexStart, 
		Name::indexInLMMTenorStructure  indexEnd, 
		Tenor    floatingLegTenorType,
		Tenor	fixedLegTenorType,
		Tenor    lmmTenorStructureTenorType);


	double get_strike() const {return strike_;}
	void   set_strike(double strike) {strike_ = strike;}

	Tenor get_floatingLegTenorType()		  const {return floatingLegTenorType_;}
	Tenor get_fixedLegTenorType()		  const {return fixedLegTenorType_;}
	Tenor get_lmmTenorStructureTenorType() const {return lmmTenorStructureTenorType_; }

	//size_t get_floatingLegTenorLmmTenorRatio() const { return TenorType::TenorTypeRatio(floatingLegTenorType_,lmmTenorStructureTenorType_);}		
	size_t get_fixedLegTenorLmmTenorRatio()    const { return fixedLegTenorType_.ratioTo( lmmTenorStructureTenorType_);}


	const std::vector<Name::indexInLMMTenorStructure>& get_floatingLegPaymentIndexSchedule() const {return floatingLegPaymentIndexSchedule_;}
	const std::vector<Name::indexInLMMTenorStructure>& get_fixedLegPaymentIndexSchedule() const {return fixedLegPaymentIndexSchedule_;}

	Name::indexInLMMTenorStructure get_indexStart() const {return indexStart_;}
	Name::indexInLMMTenorStructure get_indexEnd() const {return indexEnd_;}


public:
	void print() const;
	void print_details() const;
};
typedef boost::shared_ptr<VanillaSwap> VanillaSwap_PTR;


}


