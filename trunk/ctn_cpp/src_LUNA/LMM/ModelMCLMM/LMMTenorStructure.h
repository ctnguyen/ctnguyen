#ifndef LMM_TENOR_STRUCTURE_H
#define LMM_TENOR_STRUCTURE_H
#pragma once



#include <vector>
#include <string>
#include <cassert>

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

#include <LMM/Name.h>
#include <LMM/instrument/TenorType.h>


/*! \class LMMTenorStructure 
 *  Implement the structure of LMM model
 *   - number of setlement dates ,T_k, k from 0 to N (horizon)   
 *   - the setlement date set (tenorDates)    (converted to year unit)
 *   - the tenor set (\tau_k)                 (converted to year unit)
 */
class LMMTenorStructure
{

	//! tau_i = T_{i+1} - T_i
	const Tenor          tenorType_   ;    // eg: "6M" // never change, to be constant
	Name::indexInLMMTenorStructure horizon_     ;    // N 
	std::vector<double>  tenorDates_  ;    // size = N+2, T_0, T_1,  ......... T_{N+1}
	std::vector<double>  tenorDeltaT_ ;    // size = N+1, \tau_0, \tau_1,...\tau_{N+1}

public:

	//! constructor
	LMMTenorStructure(const Tenor&  tenorType, const size_t horizonYear);

	//! getter
	const Tenor& get_tenorType()                           const ;

	Name::indexInLMMTenorStructure get_horizon()           const ;
	
	const double&              get_deltaT(size_t index)    const ;
	const std::vector<double>& get_deltaT(            )    const ;
	
	const double&              get_tenorDate(size_t index) const ;
	const std::vector<double>& get_tenorDate(            ) const ;

	
	//! equal operator: 
    bool operator == (const LMMTenorStructure& LMMTenorStructure) const;
	bool operator != (const LMMTenorStructure& LMMTenorStructure) const;

	//! print in Excel
	void print(const std::string& filename) const;
};

typedef boost::shared_ptr<const LMMTenorStructure> ConstLMMTenorStructure;

#endif /* LMM_TENOR_STRUCTURE_H */
