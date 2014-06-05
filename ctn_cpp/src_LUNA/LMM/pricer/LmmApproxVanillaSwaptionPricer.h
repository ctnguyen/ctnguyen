#ifndef LMM_PRICER_APPROXVANILLASWAPTIONPRICER_H
#define LMM_PRICER_APPROXVANILLASWAPTIONPRICER_H
#pragma once

#include <cassert>

#include <boost/shared_ptr.hpp>

#include <LMM/numeric/NumericalMethods.h>
#include <LMM/instrument/VanillaSwaption.h>
#include <LMM/ModelMCLMM/Lmm.h>
#include <LMM/ModelMCLMM/Dispersion.h>
#include <LMM/pricer/VanillaSwapPricer.h>


/*! \class LmmApproxVanillaSwaptionPricer
 *  Defining approx methods for swaption pricing
 *  to use the precalculation.
 */
class LmmApproxVanillaSwaptionPricer : public VanillaSwapPricer
{

public:
	//! constructor  
	LmmApproxVanillaSwaptionPricer(const Lmm_PTR& lmmModel, const VanillaSwaption& swaption);

	//! destructor
	virtual ~LmmApproxVanillaSwaptionPricer();

	double volBlack(const VanillaSwaption& vanillaSwaption, const std::vector<double>& liborsInitValue) const;

	void accumulateShiftedSwapRateAndStrike(
		double& out_shifted_swapRate_T0 ,
        double& out_shifted_strike      ,
		const std::vector<double> & bonds_T0        ,
		const std::vector<double> & libor_shifts    ,
		const std::vector<size_t> & floatingIndices ,
		const double              & annuity_T0) const;

	//! Andrien THAI 2013 7.3.3, exactly formula is (7.17) p.32
	double computeRebonatoVolatility(
		const Array& x,
		size_t swapStartDateIndex, 		                             
	    const double & shifted_swapRate_T0,
	    const double & annuity_T0   , 
	    const std::vector<size_t> & floatingIndices,
		const std::vector<double> & bonds_T0       ,
		const std::vector<double> & libors_T0      ,
		const std::vector<double> & libor_shifts) const;

private:

    Lmm_PTR lmm_;

	/*! Each time giving a Libor vector at date zero L_i(0), we can compute the correspondant values as
	 *
	 *       Zero Coupon, Numeraire, Omega_i(0), Anuity_i(0)
	 *
	 * For the calcul of \omega_i(0) see Brigo 2006, p.239 (6.34) or Adrien THAI p.31
	 *
	 * ATTENTION Omega vector only store \omega from indexStart to indexEnd of Swap for calculating the approximation of SwapRate
	 * there are a shifted indices in relation to Libor indices
	 */
	mutable std::vector<double> buffer_ZC        ;  // buffer_ZC[i] = P(T_0, T_i), so buffer_ZC[0] = 1.0
	mutable std::vector<double> buffer_numeraire ;  // buffer_numeraire[i] = 1/buffer_ZC[i]
	mutable std::vector<double> buffer_omega     ;  // omega_[i] = deltaT_floating[i] P(T_0,T_{i+1}) / annuity
	mutable double              buffer_anuity    ;

private:
	
	//! precalculated has to do in this order : ZeroCoupon --> Numeraires --> Anuities --> Omegas

	void preCalculateNumeraireAndZC(const std::vector<double> & liborsInitValue) const ;
	void preCalculateAnuity        (const std::vector<double> & liborsInitValue, const VanillaSwaption& vanillaswaption ) const ;
	void preCalculateOmega         (const std::vector<double> & liborsInitValue, const VanillaSwaption& vanillaswaption ) const ;
	void preCalculateALL           (const std::vector<double> & liborsInitValue, const VanillaSwaption& vanillaswaption ) const ; //ctntodo this method tobe public

	double omega0(size_t i, const double& annuity_T0, const std::vector<double>& bonds_T0) const;

	//double annuity0(const VanillaSwap& vanillaSwap)const;
	//double omega0(size_t i) const;
};



	//double computeRebonatoVolatility(size_t swapStartDateIndex, 
	//								 double shifted_swapRate_T0,
	//                                 double annuity_T0, 
	//                                 const std::vector<size_t>& floatingIndices,
	//	                             const std::vector<double>& bonds_T0,
	//							     const std::vector<double>& libors_T0,
	//							     const std::vector<double>& libor_shifts);



	//double RebonatoApprox(size_t swapStartDateIndex,
	//	                  double strike,
	//					  const std::vector<size_t>& floatingIndices,
	//					  double& out_vol_squared,
	//	                  double swapRate_T0, 
	//	                  double annuity_T0,
	//					  const std::vector<double>& bonds_T0,
	//					  const std::vector<double>& libors_T0,
	//					  const std::vector<double>& libor_shifts);


	////-- Computes Rebonato's formula for swaptions
	////-- For calibration
	//double Rebonato_SwaptionPrice(NumericalMethods& NM,
	//	                      double shifted_swapRate_T0, 
	//                          double strike, 
	//						  double vol_squared, 
	//						  double annuity);


	//double AndersenApprox();

	//const std::vector<double>& getTenorDates();
//
//};

#endif /* LMM_PRICER_APPROXVANILLASWAPTIONPRICER_H */
