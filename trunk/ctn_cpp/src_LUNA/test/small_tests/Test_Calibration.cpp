#define BOOST_TEST_MODULE LMM_test_calibration
#include <boost/test/included/unit_test.hpp>

#include <LMM/generic_path.h>
#include <LMM/helper/Printer.h>

#include <LMM/calibration/Calibration.h>



BOOST_AUTO_TEST_SUITE(lmm_calibration)


BOOST_AUTO_TEST_CASE(test_swaption_vol_ATM_calibration)
{
	//	#pragma region Calibration
	/*
		//-- Create all matrices (swap rates, vol, ...) needed for calibration
		//matrix_ swaptionMatrix;
		matrix_ strikes;
		matrix_ swapRates;
		matrix_ annuities;
		indexMatrix floatingIndexMatrix;

		
		size_t floatingTenor_calibration = 12;
		size_t fixingTenor_calibration = 12;
		size_t fix_float_ratio = fixingTenor_calibration/floatingTenor_calibration;

		
		matrix_pairOfYears matrix_of_years = DateCreator::createSwaptionMatrixDates_Years(N+2,floatingTenor_calibration/12.);
		matrix_pairOfMonths matrix_of_months = DateCreator::convertSwaptionDates_YearsToMonths(matrix_of_years);
		matrix_pairOfIndices matrix_of_indices = DateCreator::convertSwaptionDates_MonthsToIndices(floatingTenor_calibration/12.,matrix_of_months);

		matrix_pairOfYears truncatedMatYears = mktInfoHandler.chooseSwapMaturitiesAndTenors(10,matrix_of_years);

		Approximation approx2(vol,tenorDates);

		//-- Modifier/enlever 
		// renommer bonds en dsicount factors
		//-- Create swaption matrix, as well as swap rates, strikes, annuities
		matrix_ swaptionMatrix2 = SwaptionCreator::createSwaptionMatrix(matrix_of_indices,
																	   floatPer, // = Libor tenor
											                           floatingTenor_calibration,
																	   fixingTenor_calibration,	
																	   strikes,
																	   swapRates,
																	   annuities,
																	   floatingIndexMatrix,
										                               bonds_0,
										                               libors_init,
											                           liborShifts,
											                           approx2);


		matrix_ newSwaptionMat = mktInfoHandler.chooseSwaptionMatrix(10); // Do calibration for tenor swap =  1Y to 10Y
		matrix_ newSwapRateMat = mktInfoHandler.chooseSwapRates(10);
		matrix_ newStrikes = newSwapRateMat;

		//-- TODO : Compute annuities and pairs of indices


		std::ofstream ofstr;
		ofstr.open("E:\\SwaptionVolMatrix.xls");
		for (size_t i = 0; i < h.size(); ++i)
		{
			for (size_t j = 0; j < h[i].size(); ++j)
				ofstr << h[i][j] << "\t";

			ofstr << endl;
		}
		ofstr << endl;
		DateCreator::printMatrixOfIndices(ofstr,matrix_of_indices);
		SwaptionCreator::print_swaptionMatrix(ofstr,swaptionMatrix2);

		ofstr.close();

		matrix_ weights(N+1,std::vector<double>(N+1)); 
		matrix_ weights_maturity(N+1,std::vector<double>(N+1)); 
		matrix_ weights_tenor(N+1,std::vector<double>(N+1)); 
		matrix_ weights_maturity_2(N+1,std::vector<double>(N+1)); 
		matrix_ weights_tenor_2(N+1,std::vector<double>(N+1)); 

		for (size_t i = 1; i < N+1; ++i)
		{
			for (size_t j = 1; j <= i; ++j)
			{
				weights[i][j] = 1.;
				weights_maturity[i][j] = 1.;
				weights_tenor[i][j] = 1.;
				weights_maturity_2[i][j] = 1.;
				weights_tenor_2[i][j] = 1.;
			}
		}


		matrix_ h_initialguess(N+1,std::vector<double>(N+1,0.));
		
		for (size_t i = 1; i < N+1; ++i)
		{
			for (size_t j = 1; j <= i; ++j)
			{
                h_initialguess[i][j] = h[i][j]*(1 + (rand()*0.3)/RAND_MAX);
			}
		}

		Array startValues = vol.map_MatrixToArray(h_initialguess);
		//NumericalMethods NM;
		
		//-- Create cost function 
		SwaptionApproxCostFunction mycostfunction(swaptionMatrix2,
			                                strikes,											
											floatingIndexMatrix,
										    swapRates,
											annuities,
											bonds_0,
											libors_init,
											liborShifts,
											approx,
											
											weights,
											weights_maturity,
											weights_tenor,
											weights_maturity_2,
											weights_tenor_2);


		cout << "Number of variables: " << nbVolalities << endl << endl;

		ofstream outputFile;
		outputFile.open("E:\\calibration_results.xls");

		outputFile << "index libor/dates" << "\t";
		for (size_t i = 0; i < N+1; ++i)
			outputFile << tenorDates[i] << "\t";

		outputFile << endl;

		//-- Write initial vol matrix in xls file
		outputFile << endl << "Libor vol matrix -- Initial guess" << endl;
		for (size_t i = 0; i < N+1; ++i)
		{
			outputFile << "\t";
			for (size_t j = 0; j < N+1; ++j)
				outputFile << h_initialguess[i][j] << "\t";

			outputFile << endl;
		}
		outputFile << endl;

		outputFile << endl << "Libor Vol matrix -- Model Input" << endl;

		//-- Save matrix h (input) in a xls file
		vol.saveMatrix(outputFile); 

		Calibration calibrator;
		Array liborVolArray = calibrator.Calibrate(outputFile,mycostfunction,startValues);

		
		//-- Write swaption vol matrix in xls
		outputFile << endl << "Swaption vol matrix (Rebonato)" << endl;
		for (size_t i = 0; i < swaptionMatrix2.size(); ++i)
		{
			outputFile << "\t";
			for (size_t j = 0; j < swaptionMatrix2[i].size(); ++j)
			{
				outputFile << swaptionMatrix2[i][j] << "\t";
			}

			outputFile << endl;
		}
		outputFile << endl;

		

		//------------------------------------------------------------------//
		//               compute swaption vol after calibration             //
		//------------------------------------------------------------------//

		//matrix_ liborVolMatrix_output = mycostfunction.map_ArrayToMatrix(liborVolArray);

		matrix_ liborVolMatrix_output = vol.map_ArrayToMatrix(liborVolArray);

		PiecewiseConstantVolatility vol_calibrated(liborVolMatrix_output,tenorDates,nbFactors,N+1);

		Approximation approx_calibrated(vol_calibrated,tenorDates);

		//-- Create swaption matrix, as well as swap rates, strikes, annuities
		matrix_ swaptionMatrix3 = SwaptionCreator::createSwaptionMatrix(matrix_of_indices,
																	   floatPer, // = Libor tenor
											                           floatingTenor_calibration,
																	   fixingTenor_calibration,	
																	   strikes,
																	   swapRates,
																	   annuities,
																	   floatingIndexMatrix,
										                               bonds_0,
										                               libors_init,
											                           liborShifts,
											                           approx_calibrated);

		outputFile << endl << "Swaption vol matrix (after calibration)" << endl;
		for (size_t i = 0; i < swaptionMatrix3.size(); ++i)
		{
			outputFile << "\t";
			for (size_t j = 0; j < swaptionMatrix3[i].size(); ++j)
			{
				outputFile << swaptionMatrix3[i][j] << "\t";
			}
			outputFile << endl;
		}
		outputFile << endl;
		
		outputFile << endl << "Relative errors (swaption vol)" << endl;
		for (size_t i = 0; i < swaptionMatrix3.size(); ++i)
		{
			outputFile << "\t";
			for (size_t j = 0; j < swaptionMatrix3[i].size(); ++j)
			{
				if (swaptionMatrix2[i][j] == 0.)
					outputFile << 0. << "\t";
				else
				{
					outputFile << (swaptionMatrix2[i][j]-swaptionMatrix3[i][j])/swaptionMatrix2[i][j] << "\t";
				}
			}

			outputFile << endl;
		}
		outputFile << endl;

		outputFile.close();
		*/

	//#pragma endregion
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
