#ifndef LMM_TENOR_STRUCTURE_H
#define LMM_TENOR_STRUCTURE_H
#pragma once



#include <vector>
#include <string>
#include <cassert>

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

#include <LMM/Name.h>
#include <LMM/helper/TenorType.h>


/*! \class LMMTenorStructure used as a basis topological, timeline, timestep for simulation
 *
 *  Implement the structure of LMM model
 *   - number of setlement dates ,T_k, k from 0 to N+1 (horizon)   
 *   - the setlement date set (tenorDates)    (converted to year unit)
 *   - the tenor set (\tau_k)                 (converted to year unit)
 *
 *     T[i]    0   1    2    3    ...                    N+1
 * timeline    *---*----*----*---*----*----*---*----*----*   \\ horizon_ = N
 *  \tau[i]      0   1    2                            N
 * use  L_i      0   1    2                            N
 *
 * T_{i+1}-T_i = \tau_i   <-- use of -->   L_i = L(t,T_i,T_{i+1})
 *
 * /!\ The reason there are N+1 date because in our code, N is a number of LIBORs
 *     Our convention  : L_i is the forward LIBOR L(t,T_i,T_{i+1}), i-LiborIndex run from 1 to N
 *     Hence for having N LIBORs, we create N+2 dates nodes
 */
class LMMTenorStructure //ctntodo this class has to be singleton
{
public:

	/*! constructor
	 * - compute from number of years into multiple of tenortyp --> horizon N=nbYear*12/TenorType.nbMonth 
	 * - compute and store T[i], \tau[i]
	 */
	LMMTenorStructure(const Tenor&  tenorType, const size_t nbYear);

	//! getter
	const Tenor& get_tenorType()                           const ;

	LMM::Index get_horizon()           const ;
	
	const double&              get_deltaT(size_t index)    const ;
	const std::vector<double>& get_deltaT(            )    const ;
	
	const double&              get_tenorDate(size_t index) const ;
	const std::vector<double>& get_tenorDate(            ) const ;
	
	//! equal operator: 
    bool operator == (const LMMTenorStructure& LMMTenorStructure) const;
	bool operator != (const LMMTenorStructure& LMMTenorStructure) const;

	//! print in Excel
	void print(const std::string& filename) const;

private:

	const Tenor          tenorType_   ;    // eg: "3M", "6M", "9M" smallest timestep for simulation 
	LMM::Index           horizon_     ;    // N 
	std::vector<double>  tenorDates_  ;    // size = N+2, T_0, T_1,  ......... T_{N+1}
	std::vector<double>  tenorDeltaT_ ;    // size = N+1, \tau_0, \tau_1,...\tau_{N}
};

typedef boost::shared_ptr<const LMMTenorStructure> ConstLMMTenorStructure;

#endif /* LMM_TENOR_STRUCTURE_H */
