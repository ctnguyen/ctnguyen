#include <LMM/ModelMCLMM/McSpotLmm.h>




McSpotLmm::McSpotLmm(const Dispersion&                  dispersion,
					 const std::vector<double>&         shifts,
					 const std::vector<double>&         liborsInitValue,
					 RNGenerator_PTR                    rnGenerator,
					 MCSchemeType::MCSchemeType			mcSchemeType)
					 :McLmm(dispersion,shifts,liborsInitValue,rnGenerator,mcSchemeType)
{};


void McSpotLmm::simulateLMM()
{
	//! YY slow ? 
	switch(mcSchemeType_)
	{
	case MCSchemeType::MCSchemeType::EULER:
		SpotLmmModel_Euler();
		break;
	case MCSchemeType::MCSchemeType::PC:
		SpotLmmModel_Pc();
		break;
	case MCSchemeType::MCSchemeType::IPC: // improved predictor-corrector
		SpotLmmModel_Ipc();
		break;
	default:
		break;
	}
	computeNumeraires();
}



//! numeraires_[i] = \prod_{k=0}^{i-1} 1/P(T_k,T_{k+1}), esp: numeraires_[0] = 1.0.
//! recursive relation: numeraires_[i+1] = numeraires_[i]/P(T_i,T_{i+1}), with init condition: numeraires_[0] = 1.0.
//! 1/P(T_k,T_{k+1}) = 1+deltaT[k]*Libor_k(T_k)
void McSpotLmm::computeNumeraires()
{
	const std::vector<double>& deltaTVector = dispersion_.get_lmmTenorStructure().get_deltaT();

	//! init condition:
	numeraires_[0] = 1.0;

	//! recursive condition:
	for (size_t indexNumeraire = 1; indexNumeraire < numeraires_.size(); ++indexNumeraire)
	{
		size_t indexLibor = indexNumeraire-1;
		size_t indexT     = indexLibor;

		double deltaT     = deltaTVector[indexLibor];
		double libor      = liborMatrix_(indexLibor,indexT);
		numeraires_[indexNumeraire] = numeraires_[indexNumeraire-1]*(1+deltaT*libor);
	}
}


void McSpotLmm::SpotLmmModel_Euler()
{
	size_t nbFactors = dispersion_.getNbFactors();
	std::vector<Real>   gaussian_tmp(nbFactors,0.); 
	const std::vector<double>& deltaT = dispersion_.get_lmmTenorStructure().get_deltaT();
	std::vector<double> drift_coeff(horizon_+1); // working place: delta_k*libor_k/(1+delta_k*libor_k)

	// Compute each Libor rate's value at every tenor date (except at time 0)
	for (size_t indexTime = 1; indexTime <= horizon_; ++indexTime)                // forward indexTime: 1->N   
	{ 
		rnGenerator_->generate(gaussian_tmp);  // generate Gaussian.

		//! precalculate: drift_coeff.
		size_t indexBeta = indexTime; // T_{beta(t)-1} <= t < T_{beta(t)}
		for(size_t k = indexBeta; k<=horizon_; ++k)  // k : is a Libor index
		{
			double libor_k = liborMatrix_(k,indexTime-1);
			double shift_k = shifts_[k];
			double delta_k = deltaT[k];
			drift_coeff[k] = delta_k*(libor_k+shift_k) / (1+ delta_k*libor_k); // Positive drift !
		}

		for (size_t indexLibor = indexTime; indexLibor <= horizon_; ++indexLibor)  // Backward indexLibor: N -> indexTime   i
		{ 		 
			//! integral on: [indexTime-1, indexTime] 
			Real diffusion_factor = -0.5 * covarianceTensor_(indexTime, indexLibor, indexLibor)
				+computeIntSto(indexTime,indexLibor,gaussian_tmp); 

			double drift_factor = 0.0;
			for(size_t k = indexBeta; k<=indexLibor; ++k)
			{
				drift_factor += drift_coeff[k] * covarianceTensor_(indexTime, k, indexLibor);
			}

			liborMatrix_(indexLibor,indexTime) = (liborMatrix_(indexLibor,indexTime-1) + shifts_[indexLibor] ) * std::exp(diffusion_factor + drift_factor) - shifts_[indexLibor];
		}
	}
}



void McSpotLmm::SpotLmmModel_Pc()
{
	size_t nbFactors = dispersion_.getNbFactors();
	std::vector<Real>   gaussian_tmp(nbFactors,0.); 
	const std::vector<double>& deltaT = dispersion_.get_lmmTenorStructure().get_deltaT();
	std::vector<double> drift_coeff(horizon_+1); // working place: delta_k*libor_k/(1+delta_k*libor_k)

	for (size_t indexTime = 1; indexTime <= horizon_; ++indexTime)   // forward indexTime: 1->N   
	{ 
		rnGenerator_->generate(gaussian_tmp);  // generate Gaussian.

		//! predictor
		size_t indexBeta = indexTime; // T_{beta(t)-1} <= t < T_{beta(t)}
		for(size_t k = indexBeta; k<=horizon_; ++k)  // k : is a Libor index
		{
			double libor_k = liborMatrix_(k,indexTime-1);
			double shift_k = shifts_[k];
			double delta_k = deltaT[k];
			drift_coeff[k] = delta_k*(libor_k+shift_k) / (1+ delta_k*libor_k); // Positive drift !
		}

		for (size_t indexLibor = indexTime; indexLibor <= horizon_; ++indexLibor)  // Backward indexLibor: N -> indexTime   i
		{ 		 
			//! integral on: [indexTime-1, indexTime] 
			Real diffusion_factor = -0.5 * covarianceTensor_(indexTime, indexLibor, indexLibor)
				+computeIntSto(indexTime,indexLibor,gaussian_tmp); 

			double drift_factor = 0.0;
			for(size_t k = indexBeta; k<=indexLibor; ++k)
			{
				drift_factor += drift_coeff[k] * covarianceTensor_(indexTime, k, indexLibor);
			}

			liborMatrix_(indexLibor,indexTime) = (liborMatrix_(indexLibor,indexTime-1) + shifts_[indexLibor] ) * std::exp(diffusion_factor + drift_factor) - shifts_[indexLibor];
		}

		//! corrector
		for(size_t k = indexBeta; k<=horizon_; ++k)  // k : is a Libor index
		{
			double libor_k = liborMatrix_(k,indexTime);
			double shift_k = shifts_[k];
			double delta_k = deltaT[k];
			drift_coeff[k] = 0.5*drift_coeff[k] + 0.5*(delta_k*(libor_k+shift_k) / (1+ delta_k*libor_k)); 
		}

		for (size_t indexLibor = indexTime; indexLibor <= horizon_; ++indexLibor)  // Backward indexLibor: N -> indexTime   i
		{ 		 
			//! integral on: [indexTime-1, indexTime] 
			Real diffusion_factor = -0.5 * covarianceTensor_(indexTime, indexLibor, indexLibor)
				+computeIntSto(indexTime,indexLibor,gaussian_tmp); 

			double drift_factor = 0.0;
			for(size_t k = indexBeta; k<=indexLibor; ++k)
			{
				drift_factor += drift_coeff[k] * covarianceTensor_(indexTime, k, indexLibor);
			}

			liborMatrix_(indexLibor,indexTime) = (liborMatrix_(indexLibor,indexTime-1) + shifts_[indexLibor] ) * std::exp(diffusion_factor + drift_factor) - shifts_[indexLibor];
		}
	}
}


void McSpotLmm::SpotLmmModel_Ipc()
{
	throw("Error: not implemented yet.");
}




//-----------------------------------------------------------------------//
//                                                                       //
//                                 TESTS                                 //
//                                                                       //
//-----------------------------------------------------------------------//
//
//-- Same as original spot numeraire function, but allows different tenor dates (i.e. periods neq to 6M)
//void McSpotLmm::computeSpotNumerairesTests(size_t k, const matrix_& lmm, const std::vector<double>& tenorDates) 
//{
//	Real res = 1;
//
//	if (k != 0)
//	{
//		for (size_t j = 0; j < k; ++j) 
//		{
//			Time per = tenorDates[j+1] - tenorDates[j]; 
//			cout << "T" << j << " : " << tenorDates[j];
//			cout << " T" << j+1 << " : " << tenorDates[j+1];
//			cout << " T"<< j+1 << " - T" << j << " : " << per << endl;
//			cout << "libor : " << lmm[j][j] << endl;
//			res *= (1 + per*lmm[j][j]); 
//		}
//	}
//	cout << "Numeraire value : " << res << endl << endl;
//}
//
//void McSpotLmm::NumeraireTest()
//{
//	-- Create a fake libor matrix
//	matrix_ fakeLmmMatrix(3,std::vector<double>(3,0.));
//
//	fakeLmmMatrix[0][0] = 0.0201003; fakeLmmMatrix[0][1] = 0.; fakeLmmMatrix[0][2] = 0.;
//	fakeLmmMatrix[1][0] = 0.0251003; fakeLmmMatrix[1][1] = 0.0301003; fakeLmmMatrix[1][2] = 0.;
//	fakeLmmMatrix[2][0] = 0.0301003; fakeLmmMatrix[2][1] = 0.0351003; fakeLmmMatrix[2][2] = 0.0401003;
//
//	-- Set different periods between tenor dates 
//	std::vector<double> fakeTenorDates(4);
//	fakeTenorDates[0] = 0.;
//	fakeTenorDates[1] = 0.5; // T1 - T0 = 0.5
//	fakeTenorDates[2] = 0.75; // T2 - T1 = 0.25
//	fakeTenorDates[3] = 1.5; // T3 - T2 = 0.75
//	
//	-- Compute numeraires for all tenor dates
//	for (size_t k = 0; k < 4; ++k)
//		computeSpotNumerairesTests(k,fakeLmmMatrix,fakeTenorDates);
//}