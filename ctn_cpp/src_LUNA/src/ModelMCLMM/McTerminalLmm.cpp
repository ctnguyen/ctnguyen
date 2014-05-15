#include <LMM/ModelMCLMM/McTerminalLmm.h>
#include <LMM/ModelMCLMM/Dispersion.h>

McTerminalLmm::McTerminalLmm(const Dispersion&                  dispersion,
							 const std::vector<double>&         shifts,
							 const std::vector<double>&         liborsInitValue,
							 RNGenerator_PTR                    rnGenerator,
							 MCSchemeType::MCSchemeType			mcSchemeType)
							 :McLmm(dispersion,shifts,liborsInitValue,rnGenerator,mcSchemeType)
{};


void McTerminalLmm::simulateLMM()
{
	//! YY slow ? 
	switch(mcSchemeType_)
	{
	case MCSchemeType::MCSchemeType::EULER:
		TerminalLmmModel_Euler();
		break;
	case MCSchemeType::MCSchemeType::PC:
		TerminalLmmModel_Pc();
		break;
	case MCSchemeType::MCSchemeType::IPC: // improved predictor-corrector
		TerminalLmmModel_Ipc();
		break;
	default:
		break;
	}
	computeNumeraires();
}


//! numeriare[i]   = P(T_i, T_{N+1}), i=[1,2,...,N]
//! numeraire[N+1] = 1
//! numeraire[0]   = known at today
void McTerminalLmm::computeNumeraires() 
{
	const std::vector<double>& deltaT = dispersion_.get_lmmTenorStructure().get_deltaT();
	for (size_t i = 0; i<= horizon_; ++i)
	{
		numeraires_[i] = 1.0;
		for (size_t k = i; k <= horizon_; ++k)
		{
			numeraires_[i] *= 1/(1 + deltaT[k]*liborMatrix_(k,i));  // liborMatrix_(i,j): libor_i at time T_j
		}
	}
}

void McTerminalLmm::TerminalLmmModel_Euler()
{
	size_t nbFactors = dispersion_.getNbFactors();
	std::vector<Real>   gaussian_tmp(nbFactors,0.); 

	const std::vector<double>& deltaT = dispersion_.get_lmmTenorStructure().get_deltaT();

	std::vector<double> drift_coeff(horizon_+1); // working place: delta_k*libor_k/(1+delta_k*libor_k)

	// Compute each Libor rate's value at every tenor date (except at time 0)
	for (size_t indexTime = 1; indexTime <= horizon_; ++indexTime)                // forward indexTime: 1->N   j
	{ 
		rnGenerator_->generate(gaussian_tmp);  // generate Gaussian.
	
		//! precalculate: drift_coeff.
		for(size_t k = indexTime+1; k<=horizon_; ++k)  // k : is a Libor index
		{
			 double libor_k = liborMatrix_(k,indexTime-1);
			 double shift_k = shifts_[k];
			 double delta_k = deltaT[k];
			 drift_coeff[k] = - delta_k*(libor_k+shift_k) / (1+ delta_k*libor_k);
		}

		for (size_t indexLibor = horizon_; indexLibor >= indexTime; --indexLibor)  // Backward indexLibor: N -> indexTime   i
		{ 		 
			//! integral on: [indexTime-1, indexTime] 
			Real diffusion_factor = -0.5 * covarianceTensor_(indexTime, indexLibor, indexLibor)
				                    +computeIntSto(indexTime,indexLibor,gaussian_tmp); 

			double drift_factor = 0.0;
			for(size_t k = indexLibor + 1; k<=horizon_; ++k)
			{
				drift_factor += drift_coeff[k] * covarianceTensor_(indexTime, k, indexLibor);
			}

			liborMatrix_(indexLibor,indexTime) = (liborMatrix_(indexLibor,indexTime-1) + shifts_[indexLibor] ) * std::exp(diffusion_factor + drift_factor) - shifts_[indexLibor];
		}
	}
}



void McTerminalLmm::TerminalLmmModel_Pc()
{
	size_t nbFactors = dispersion_.getNbFactors();
	std::vector<Real>   gaussian_tmp(nbFactors,0.); 

	const std::vector<double>& deltaT = dispersion_.get_lmmTenorStructure().get_deltaT();
	std::vector<double> drift_coeff(horizon_+1); // working place: delta_k*libor_k/(1+delta_k*libor_k)

	// Compute each Libor rate's value at every tenor date (except at time 0)
	for (size_t indexTime = 1; indexTime <= horizon_; ++indexTime)                // forward indexTime: 1->N   j
	{ 
		rnGenerator_->generate(gaussian_tmp);  // YY predictor & corrector use the same BM ??? why ??? 

		//! ---- ---- ---- ---- predictor part ---- ---- ---- ---- 
		for(size_t k = indexTime+1; k<=horizon_; ++k)  // k : is a Libor index
		{
			double libor_k = liborMatrix_(k,indexTime-1);
			double shift_k = shifts_[k];
			double delta_k = deltaT[k];
			drift_coeff[k] = - delta_k*(libor_k+shift_k) / (1+ delta_k*libor_k);
		}

		for (size_t indexLibor = horizon_; indexLibor >= indexTime; --indexLibor)  // Backward indexLibor: N -> indexTime   i
		{ 		 
			//! integral on: [indexTime-1, indexTime] 
			Real diffusion_factor = -0.5 * covarianceTensor_(indexTime, indexLibor, indexLibor)
				+computeIntSto(indexTime,indexLibor,gaussian_tmp); 

			double drift_factor = 0.0;
			for(size_t k = indexLibor + 1; k<=horizon_; ++k)
			{
				drift_factor += drift_coeff[k] * covarianceTensor_(indexTime, k, indexLibor);
			}

			liborMatrix_(indexLibor,indexTime) = (liborMatrix_(indexLibor,indexTime-1) + shifts_[indexLibor] ) * std::exp(diffusion_factor + drift_factor) - shifts_[indexLibor];
		}

		//! ---- ---- ---- ---- corrector part ---- ---- ---- ---- 
		//! precalculate: drift_coeff with Libor at time: indexT-1 & indexT
		for(size_t k = indexTime+1; k<=horizon_; ++k)  // k : is a Libor index
		{
			double libor_k = liborMatrix_(k,indexTime);
			double shift_k = shifts_[k];
			double delta_k = deltaT[k];
			double drift_coeff_new_k = - delta_k*(libor_k+shift_k) / (1+ delta_k*libor_k);
			drift_coeff[k] = 0.5*drift_coeff[k] + 0.5*drift_coeff_new_k;
		}

		//! 2nd simulation of Libor: indexT-1 -> indexT
		for (size_t indexLibor = horizon_; indexLibor >= indexTime; --indexLibor)  // Backward indexLibor: N -> indexTime   i
		{ 		 
			//! integral on: [indexTime-1, indexTime] 
			Real diffusion_factor = -0.5 * covarianceTensor_(indexTime, indexLibor, indexLibor)
				+computeIntSto(indexTime,indexLibor,gaussian_tmp); 

			double drift_factor = 0.0;
			for(size_t k = indexLibor + 1; k<=horizon_; ++k)
			{
				drift_factor += drift_coeff[k] * covarianceTensor_(indexTime, k, indexLibor);
			}
			liborMatrix_(indexLibor,indexTime) = (liborMatrix_(indexLibor,indexTime-1) + shifts_[indexLibor] ) * std::exp(diffusion_factor + drift_factor) - shifts_[indexLibor];
		}

	}
}



//void McTerminalLmm::TerminalLmmModel_Pc()
//{
//	const std::vector<double>& deltaT = dispersion_.get_lmmTenorStructure().get_deltaT();
//
//	std::vector<Real> gaussian_tmp(vol_->getNbFactors(),0.);
//
//	//matrix<Rate> &lmm_pc(lmm); // YY TODO: make if more efficiently latter...
//	std::vector<double> lmm_pc(liborMatrix_.size());
//
//	// Compute each Libor rate's value at every tenor date (except at time 0)
//	for (size_t j = 1; j < horizon_+2; ++j) // time
//	{ 
//		std::vector<double> drift_temp(horizon_+1,0.);
//
//		//-- Fill the gaussian vector
//		generator_.pseudoRandomNumberGenerator(gaussian_tmp);
//
//		//! ---- predictor-part
//		for (size_t i = horizon_; i >= j; --i) // Backward simulations
//		{ 
//			Real diffusion_factor_pc = exp(-0.5 * covariance_tensor(j-1,i,i))
//									* exp(vol_->computeIntSto(i,j,covariance_tensor,gaussian_tmp));
//			Real drift_factor_pc = 1.;
//
//			// Drift computation if i < horizon_
//			if (i < horizon_) 
//			{
//				double tmp = liborMatrix_[i+1][j-1]*deltaT[i+1];
//				double tmp_shifted = (liborMatrix_(i+1,j-1)+shifts_[i+1])*deltaT[i+1];
//				drift_temp[i+1] = tmp_shifted/(1+tmp);
//
//				Real drift = 0.0;
//				for (size_t k = i+1; k < horizon_+1; ++k) 
//					drift -= drift_temp[k] * covariance_tensor[j-1][i][k];
//					
//				drift_factor_pc *= exp(drift);
//			}
//
//			lmm_pc[i] = (liborMatrix_[i][j-1]+shifts_[i])*drift_factor_pc*diffusion_factor_pc - shifts_[i];
//		}
//
//		//! ---- corrector-part
//		for (size_t i = horizon_; i >= j; --i) // Backward simulations
//		{ 
//			Real diffusion_factor = exp(-0.5 * covariance_tensor(j-1,i,i))
//									* exp(vol_->computeIntSto(i,j,covariance_tensor,gaussian_tmp));
//			Real drift_factor = 1.;
//
//			// Drift computation if i < horizon_
//			if (i < horizon_) 
//			{
//				double tmp  = lmm_pc[i+1]*deltaT[i+1];   // t + Delta_t
//				double tmp2 = liborMatrix_(i+1,j-1)*deltaT[i+1];  // t
//
//				double tmp_shifted = (lmm_pc[i+1]+shifts_[i+1])*deltaT[i+1];
//				double tmp2_shifted = (liborMatrix_(i+1,j-1)+shifts_[i+1])*deltaT[i+1];
//
//				drift_temp[i+1] = 0.5*( tmp_shifted/(1+tmp) + tmp2_shifted/(1+tmp2) ); 
//
//				Real drift = 0.0;
//				for (size_t k = i+1; k < horizon_+1; ++k) 
//					drift -= drift_temp[k] * covariance_tensor[j-1][i][k];
//					
//				drift_factor *= exp(drift);
//			}
//
//			liborMatrix_[i][j] = (liborMatrix_(i,j-1)+shifts_[i])*drift_factor*diffusion_factor - shifts_[i];
//		}
//	}
//}

void McTerminalLmm::TerminalLmmModel_Ipc()
{
	size_t nbFactors = dispersion_.getNbFactors();
	std::vector<Real>   gaussian_tmp(nbFactors,0.); 

	const std::vector<double>& deltaT = dispersion_.get_lmmTenorStructure().get_deltaT();

	std::vector<double> drift_coeff_predictor(horizon_+1); // working place: delta_k*libor_k/(1+delta_k*libor_k)
	std::vector<double> drift_coeff_corrector(horizon_+1); // working place: delta_k*libor_k/(1+delta_k*libor_k)

	// Compute each Libor rate's value at every tenor date (except at time 0)
	for (size_t indexTime = 1; indexTime <= horizon_; ++indexTime)                // forward indexTime: 1->N   j
	{ 
		rnGenerator_->generate(gaussian_tmp);  // YY predictor & corrector use the same BM ??? why ??? 

		////! ---- ---- ---- ---- predictor part ---- ---- ---- ---- 
		//! 1st simulation of Libor: indexT-1 -> indexT
		for (size_t indexLibor = horizon_; indexLibor >= indexTime; --indexLibor)  // Backward indexLibor: N -> indexTime   i
		{ 		 
			//! integral on: [indexTime-1, indexTime] 
			Real diffusion_factor = -0.5 * covarianceTensor_(indexTime, indexLibor, indexLibor)
				+computeIntSto(indexTime,indexLibor,gaussian_tmp); 

			//! calculate one new drift term at this step:
			if(indexLibor < horizon_) // predictor need Libor at current time calculated at last step.
			{
				size_t k			   = indexLibor +1; 
				double libor_k_last    = liborMatrix_(k,indexTime-1);
				double libor_k_current = liborMatrix_(k,indexTime);
				double shift_k		   = shifts_[k];
				double delta_k		   = deltaT[k];
				drift_coeff_predictor[k] = - delta_k*(libor_k_last+shift_k) / (1+ delta_k*libor_k_last);
				drift_coeff_corrector[k] = - delta_k*(libor_k_current+shift_k) / (1+ delta_k*libor_k_current);
			}
			
			double drift_factor = 0.0;
			for(size_t k = indexLibor + 1; k<=horizon_; ++k)
			{
				drift_factor += 0.5*(drift_coeff_predictor[k] + drift_coeff_corrector[k])* covarianceTensor_(indexTime, k, indexLibor);
			}

			liborMatrix_(indexLibor,indexTime) = (liborMatrix_(indexLibor,indexTime-1) + shifts_[indexLibor] ) * std::exp(diffusion_factor + drift_factor) - shifts_[indexLibor];
		}
	}
}




//void McTerminalLmm::TerminalLmmModel_Euler()
//{
//	const std::vector<double>& deltaT = dispersion_.get_lmmTenorStructure().get_deltaT();
//
//	size_t nbFactors = dispersion_.getNbFactors();
//	std::vector<double> drift_temp(horizon_+1,0.);
//	std::vector<Real>   gaussian_tmp(nbFactors,0.); 
//	
//	// Compute each Libor rate's value at every tenor date (except at time 0)
//	for (size_t j = 1; j <= horizon_; ++j)  // forward indexTime: j: 1->N
//	{ 
//		generator_.generate(gaussian_tmp);  // generate Gaussian.
//
//		for (size_t i = horizon_; i >= j; --i)  // Backward indexLibor
//		{ 		 
//			//Real diffusion_factor = exp(-0.5 * covariance_tensor[j-1][i][i])
//			//				* exp(vol_->computeIntSto(i,j,covariance_tensor,gaussian_tmp));
//
//			//------------------ TODO HERE, not sure the LMM is of good format ---------------
//			//Real diffusion_factor = exp(-0.5 * covarianceTensor_(j-1,i,i))
//			//	* exp(vol_->computeIntSto(i,j,covariance_tensor,gaussian_tmp));
//
//			Real diffusion_factor = exp(-0.5 * covarianceTensor_(j-1,i,i))
//									* exp(vol_->computeIntSto(i,j,covariance_tensor,gaussian_tmp));
//
//			Real drift_factor = 1.0;
//			
//			// Drift computation if i < horizon_
//			if (i < horizon_) {
//
//				double tmp = liborMatrix_(i+1,j-1)*deltaT[i+1];
//				double tmp_shifted = (liborMatrix_(i+1,j-1)+shifts_[i+1])*deltaT[i+1];
//				drift_temp[i+1] = tmp_shifted/(1+tmp);
//
//				Real drift = 0.;
//				for (size_t k = i+1; k < horizon_+1; ++k) 
//					drift -= drift_temp[k] * covariance_tensor(j-1,i,k);
//
//				drift_factor *= exp(drift);
//			}
//
//			//-- Drift accumulation for MC variance computing
//			cumulated_drifts_(i,j) += drift_factor;
//			cumulated_squared_drifts_(i,j) += drift_factor*drift_factor;
//
//			liborMatrix_(i,j) = (liborMatrix_(i,j-1) + shifts_[i] )*drift_factor*diffusion_factor - shifts_[i];
//		}
//	}
//}
//-----------------------------------------------------------------//
//                                                                 //
//                             TESTS                               //
//                                                                 //
//-----------------------------------------------------------------//
//
//
//void McTerminalLmm::testTerminalNumeraires()
//{
//	//-- Do one libor simulation
//	LmmSimulation(euler);
//
//	//-- Print libor matrix
//	printLiborMatrix();
//
//	//-- Compute terminal numeraires P(Tk,TN+1) for all k=0,...,N+1
//	numeraires_[horizon_+1] = 1.;
//	for (size_t k = horizon_; k >= 0; --k)
//	{
//		cout << "---- numeraire P(T" << k << ",TN+1) : " << endl;
//		numeraires_[k] = 1.;
//		for (size_t j = k; j < horizon_+1; ++j)
//		{
//			Real per = this->deltaT_[j];
//			cout << "Libor L" <<j << "(T" << k << ") : " << liborMatrix_[j][k] << endl;
//			numeraires_[k] *= 1/(1 + per*liborMatrix_[j][k]);
//		}
//		cout << "numeraire value : " << numeraires_[k] << endl;
//		cout << endl;
//	}
//}