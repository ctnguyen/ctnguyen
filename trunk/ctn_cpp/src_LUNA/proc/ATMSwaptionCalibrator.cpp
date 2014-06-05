
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <boost/numeric/ublas/io.hpp>

#include <time.h>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

#include <LMM/generic_path.h>
#include <LMM/numeric/Interpolation.h>
#include <LMM/numeric/NumericalMethods.h>
#include <LMM/helper/QMcGenerator.h>
#include <LMM/helper/MarketInfoCollector.h>
#include <LMM/helper/MarketInfoHandler.h>
#include <LMM/pricer/McPricer.h>
#include <LMM/pricer/LmmSwaptionPricer.h>
#include <LMM/calibration/Calibration.h>
//#include "DateCreator.h"
//#include "SwaptionCreator.h"




//#include "MC.h"
//#include "TestPricing.h"
//#include "SwapModelMc.h"
//#include "instrument.h"
////#include "Swap.h"
////#include "Approximation.h"
//#include "CapletTests.h"
//#include "LiborSimulationTests.h"
//#include "SwaptionPricingTests.h"
//#include "LmmCapletPricer.h"
//#include "PiecewiseConstantVolatility.h"
//#include "LmmTarnPricer.h"
//#include "PiecewiseConstantVolatility.h"
//#include "VolatilityGridBuilder.h"


using namespace std;
using namespace boost;
using namespace QuantLib;


const size_t nbMCSimulation = 1; // Number of MC simulations
#include <vector>

int main()
{
//	using namespace numeric::ublas;
//
//	try
//	{
//		//VolatilityGridBuilder::test_insertPillarsInGrid();
//
//		/*std::vector<double> pillarValues(10);
//		for (size_t i = 0; i < pillarValues.size(); ++i)
//			pillarValues[i] = i+1;
//
//		VolatilityGridBuilder gridBuilder(10,2,pillarValues);
//		gridBuilder.printGrid("E:\\test_grid_calib.csv");*/
//
//	#pragma region Market Data
//

		std::string market_data_file = LMM::get_runtime_datapath() + "Mkt_info_1.csv";
		MarketInfoCollector::readMarketInfo(market_data_file);
		
		//-- libor tenor = 6M 
		std::vector<double> libors_BB = MarketInfoCollector::get_libors();
		std::vector<double> zc_BB = MarketInfoCollector::get_zcBonds();
		std::vector<double> zcMaturities_BB = MarketInfoCollector::get_zcMaturities();
		matrix_ swaptionMatrix_BB = MarketInfoCollector::get_swaptionVolatilityMatrix();
		matrix_ swaprates_BB = MarketInfoCollector::get_swapRates();

	
		MarketInfoHandler mktInfoHandler(libors_BB,zc_BB,zcMaturities_BB,swaptionMatrix_BB,swaprates_BB);
		mktInfoHandler.convertBpToPercent();
		//ctntodo to uncomment this two lines
		mktInfoHandler.interpolateDiscountFactors();
		std::vector<double> zcVector_BB = mktInfoHandler.createDiscountFactorArray();
//		
//	#pragma endregion
//
//	
//
//	#pragma region Set Parameters
//
//		//MarketInfoCollector::test_reader();
//		
//		Real a = -0.06; 
//		Real b = 0.40; 
//		Real c = 0.54; 
//		Real d = 0.10;
//
//		std::vector<Real> abcdParams(4);
//		abcdParams[0] = a;
//		abcdParams[1] = b;
//		abcdParams[2] = c;
//		abcdParams[3] = d;
//
//		size_t floatPer = 6;
//		size_t fixPer = 12;
//		Real tenorLibor = ((double)floatPer)/12; // = 6M per LIBOR
//
//		//size_t N = 4; // Index of the last libor 
//		size_t N = libors_BB.size()-1;
//		size_t nbFactors = 3; // number of factors for LMM
//
//	
//		//-- Set tenor periods (in years)
//		Time firstTenor = 1;
//		std::vector<Time> tenorPeriods(N+1);
//		for (size_t i = 0; i < N+1; ++i) 
//			tenorPeriods[i] = tenorLibor;
//
//		//-- Set tenor dates (in years)
//		std::vector<Time> tenorDates(N+2);
//		tenorDates[0] = 0.;
//		for (size_t i = 1; i < N+2; ++i)
//			tenorDates[i] = tenorDates[i-1] + tenorPeriods[i-1];
//
//		//-- Set adjustement coefficients for abcd vol 
//		std::vector<double> g;
//		double g_interval = 0.1;
//		double g_pace  = g_interval/N;
//		double g_start = 1-g_interval/2;
//		for (size_t i = 0; i < N+1; ++i)
//			g.push_back(g_start + i*g_pace);
//			//g.push_back(1.+rand()/((double)RAND_MAX));
//			
//
//		//-- Set volatility model
//		//DeterministicVol vol(nbFactors,N+1,abcdParams,g);
//
//
//		//-- Set piecewise cst vol parameters
//		size_t nbVolalities = 0;
//		matrix_ h(N+1,std::vector<double>(N+1,0.));
//		for (size_t i = 1; i < N+1; ++i)
//		{
//			for (size_t j = 1; j <= i; ++j)
//			{
//				//h[i][j] = (N+1-0.5*j-0.5*i)*0.2/N;
//				double Ti = tenorDates[i];
//				double Tj = tenorDates[j];
//				double tau = Ti -Tj;
//				h[i][j] = g[i] * ((a+b*tau)*exp(-c*tau)+d);
//				nbVolalities++;
//			}
//		}
//
//		
//		PiecewiseConstantVolatility vol(h,tenorDates,nbFactors,N+1);
//
//
//		cout << "Vol matrix: " << endl;
//		vol.printVolMatrix();
//		cout << endl << endl;
//
//		matrix_ h_prime(N+1,std::vector<double>(N+1,0.));
//		for (size_t i = 1; i < N+1; ++i)
//		{
//			for (size_t j = 1; j <= i; ++j)
//				h_prime[i][j] = i*10+j;
//		}
//
//		Array x = vol.map_MatrixToArray(h_prime);
//
//		//-- Shifts for each libor
//		std::vector<double> liborShifts(N+1);
//		for (size_t i = 0; i < N+1; ++i)
//			liborShifts[i] = 0.0;
//
//		Real mcPrice = -999999999.9, mcErr = -9999999999.9;
//		
//		
//	#pragma endregion
//
//	#pragma region LMM Model
//
//		std::vector<double> libors_init = libors_BB;
//
//		/*std::vector<double> libors_init(N+1);
//		for (size_t i = 0; i < N+1; ++i)
//			libors_init[i] = 0.0201003 + i*0.001;*/
//
//		//-- Model
//		//McTerminalLmm model(N,tenorPeriods,vol,liborShifts,libors_init);
//		McSpotLmm model(N,tenorPeriods,vol,liborShifts,libors_init);
//
//
//		//-- Compute covariances ( int_Tk^Tk+1 {sigma_i * sigma_j * rho_ij} )
//		std::vector<matrix_> covTensor(N+1);
//		covTensor = vol.computeAllCovariances(N,model.getTenorDates());
//		
//		
//	#pragma endregion
//
//	#pragma region Caplet Pricing
//
//		//size_t index_caplet = N; 
//		//
//		//cout << "Caplet index: " << index_caplet << endl;
//		//cout << "Number of simulations: " << M << endl;
//		//cout << "Shift : " << liborShifts[index_caplet] << endl;
//
//		////-- Take the shift into account into the caplet pricing method
//		//double strike = libors_init[index_caplet];
//
//		////-- Caplet
//		//Caplet caplet(tenorDates[index_caplet+1],tenorLibor,strike,index_caplet);
//
//		////-- Caplet pricer
//		//LmmCapletPricer capletPricer(caplet,model);
//
//		//capletPricer.test_computeCapletPrices();
//
//		//capletPricer.McCapletPrice(M,mcPrice,mcErr,libors_init,euler);
//
//		//Real lowerIc = mcPrice - 3*mcErr/sqrt((Real)M);
//		//Real upperIc = mcPrice + 3*mcErr/sqrt((Real)M);
//
//		//Real stdErr = 3*mcErr/sqrt((Real)M);
//		//cout << endl << "--- Monte-Carlo price estimate: " << mcPrice << endl;
//		//cout << "99% Confidence Interval : " << "[" << lowerIc << " ; " << upperIc << "]" << " X = " << 3*mcErr/sqrt((Real)M) << endl << endl;
//		//
//	
//		//double sigma = vol.varIntegral(index_caplet,tenorDates[index_caplet],0,tenorDates[index_caplet]);
//
//		////-- Compute numeraire P(0,T_index_caplet+1) (numeraire of the T_index_caplet_+1 forward measure)
//		//double numeraire_0 = 1.;
//		//for (size_t k = 0; k < index_caplet+1; ++k)
//		//	numeraire_0 /= (1 + tenorPeriods[k]*libors_init[k]);
//
//		//double discount = tenorPeriods[index_caplet]*numeraire_0;
//
//		//double shifted_libor_0 = libors_init[index_caplet] + liborShifts[index_caplet];
//		//double shifted_strike = strike + liborShifts[index_caplet];
//
//		//NumericalMethods blackPricer;
//
//		//double blackCapletPrice = blackPricer.BlackFormula(shifted_libor_0,shifted_strike,sigma,discount);
//
//		//cout << " : --- Black price : " << blackCapletPrice << endl << endl;
//
//		//cout << "Relative error : " << abs(blackCapletPrice-mcPrice)/blackCapletPrice << endl;
//		//cout << "absolute error : " << abs(blackCapletPrice-mcPrice) << endl;
//		//
//
//	#pragma endregion
//
//	#pragma region Swaption Pricing
//
//		size_t indexStart = 2;
//		size_t indexEnd = N+1;
//
//		size_t fixingTenor = 12; // In months
//		size_t floatingtenor = 12; // Idem
//
//		//-- Vanilla Swap
//		SwapInstruments::VanillaSwap vanillaSwap(indexStart,indexEnd,fixingTenor,floatingtenor,floatPer);
//
//
//		std::vector<size_t> floatingIndices = vanillaSwap.getFloatingPaymentIndices();
//		std::vector<size_t> fixingIndices = vanillaSwap.getFixingPaymentIndices();
//
//		size_t nbFloatingIndices = floatingIndices.size();
//		size_t nbFixingIndices = fixingIndices.size();
//
//		cout << "-- Floating indices : " << endl;
//		for (size_t i = 0; i < nbFloatingIndices; ++i)
//			cout << floatingIndices[i] << " ";
//
//		cout << endl;
//		cout << "-- Fixing indices : " << endl;
//		for (size_t i = 0; i < nbFixingIndices; ++i)
//			cout << fixingIndices[i] << " ";
//
//		cout << endl << endl;
//
//
//		//-- Set all libor dates
//		std::vector<double> dates = model.getTenorDates();
//
//		
//		//-- ZC bonds at time 0 (from Bloomberg)
//		std::vector<double> bonds_0 = zcVector_BB;
//
//		/*std::vector<double> bonds_0(N+2);
//		bonds_0[0] = 1.;
//		for (size_t i = 1; i <= N+1; ++i)
//			bonds_0[i] = bonds_0[i-1]/(1+tenorPeriods[i-1]*libors_init[i-1]);*/
//
//
//		//-- Compute Annuity at time 0
//		double annuity = 0.;
//		for each (size_t i in fixingIndices) 
//		{
//			annuity += (fixingTenor/12.)*bonds_0[i];
//		}
//
//		//-- Compute swapRate at time 0
//		double swapRate = (bonds_0[indexStart]-bonds_0[indexEnd])/annuity;
//		cout << "swapRate : " << swapRate << endl;
//
//
//		//-- Set ATM Strike
//		vanillaSwap.set_strike(swapRate);
//
//		//-- Vanilla Swaption
//		SwapInstruments::VanillaSwaption vanillaSwaption(vanillaSwap,dates);
//
//		cout << endl << "-- Dates :" << endl;
//		for (size_t i = 0; i < dates.size(); ++i)
//			cout << dates[i] << " ";
//
//		cout << endl << endl;
//
//		//-- Create the swaption pricer
//		LmmSwaptionPricer swaptionPricer(vanillaSwaption,model);
//
//		//swaptionPricer.test_computeSwaptionPrices();
//
//		//-- Compute swaption's MC price
//	//	swaptionPricer.McSwaptionPrice(M,mcPrice,mcErr,vanillaSwap,libors_init,ipc);
//
//
//		Real estimatedStdErr = 3*mcErr/sqrt((Real)M);
//		Real lowerIc = mcPrice - estimatedStdErr;
//		Real upperIc = mcPrice + estimatedStdErr;
//
//		cout << "Number of MC simulations : " << M << endl << endl;
//		cout << "----- Monte-Carlo price : " << mcPrice << endl << endl;
//		cout << "Estimated standard error : " << estimatedStdErr << endl;
//		cout << "99% confidence interval : " << "[" << lowerIc << " ; " << upperIc << "]" << endl;
//		cout << endl << endl;
//		
//
//	#pragma region Swaption Approximation 
//
//		NumericalMethods nm;
//
//		Approximation approx(vol,dates);
//		double squaredRebonatoVol = 9999.9999;
//		double strike = vanillaSwaption.getUnderlyingSwap().get_strike();
//		
//		double rebonatoPrice = approx.RebonatoApprox(indexStart,strike,floatingIndices,squaredRebonatoVol,swapRate,annuity,bonds_0,libors_init,liborShifts);
//		cout << "----- Rebonato price : " << rebonatoPrice << endl << endl;
//		cout << "ERREUR ABSOLUE : " << mcPrice - rebonatoPrice << endl;
//		cout << "STD ERROR  : " << estimatedStdErr << endl;
//		cout << "Erreur relative : " << (mcPrice-rebonatoPrice)/mcPrice << endl;
//
//		cout << "Computed rebonato vol : " << sqrt(squaredRebonatoVol) << endl << endl;
//		
//		
//		double shifted_swapRate = swapRate;
//		double shifted_strike = strike;
//		approx.accumulateShiftedSwapRateAndStrike(shifted_swapRate,shifted_strike,bonds_0,liborShifts,floatingIndices,annuity);
//		double impliedVol = nm.impliedVolatility(rebonatoPrice,shifted_strike,shifted_swapRate,annuity);
//		cout << "Implied Vol : " << impliedVol << endl;
//
//		//-- Test of the new rebonato method (for calibration) 
//		Array x_prime = vol.map_MatrixToArray(h);
//		double newvol = approx.computeRebonatoVolatility(x_prime,indexStart,shifted_swapRate,annuity,floatingIndices,bonds_0,libors_init,liborShifts);
//		cout << "computed vol (squared) with new method : " << newvol << endl; 
//		cout << "computed vol : " << sqrt(newvol) << endl;
//		 
//		double newRebonatoPrice = approx.Rebonato_SwaptionPrice(nm,shifted_swapRate, shifted_strike, newvol, annuity);
//		cout << "Rebonato Price with the new method : " << newRebonatoPrice << endl << endl << endl;
//			
//	#pragma endregion
//
//
//	#pragma endregion
//
//	#pragma region Calibration
//
//		//-- Create all matrices (swap rates, vol, ...) needed for calibration
//		//matrix_ swaptionMatrix;
//		matrix_ strikes;
//		matrix_ swapRates;
//		matrix_ annuities;
//		indexMatrix floatingIndexMatrix;
//
//		
//		size_t floatingTenor_calibration = 12;
//		size_t fixingTenor_calibration = 12;
//		size_t fix_float_ratio = fixingTenor_calibration/floatingTenor_calibration;
//
//		
//		matrix_pairOfYears matrix_of_years = DateCreator::createSwaptionMatrixDates_Years(N+2,floatingTenor_calibration/12.);
//		matrix_pairOfMonths matrix_of_months = DateCreator::convertSwaptionDates_YearsToMonths(matrix_of_years);
//		matrix_pairOfIndices matrix_of_indices = DateCreator::convertSwaptionDates_MonthsToIndices(floatingTenor_calibration/12.,matrix_of_months);
//
//		matrix_pairOfYears truncatedMatYears = mktInfoHandler.chooseSwapMaturitiesAndTenors(10,matrix_of_years);
//
//		Approximation approx2(vol,tenorDates);
//
//		//-- Modifier/enlever 
//		// renommer bonds en dsicount factors
//		//-- Create swaption matrix, as well as swap rates, strikes, annuities
//		matrix_ swaptionMatrix2 = SwaptionCreator::createSwaptionMatrix(matrix_of_indices,
//																	   floatPer, // = Libor tenor
//											                           floatingTenor_calibration,
//																	   fixingTenor_calibration,	
//																	   strikes,
//																	   swapRates,
//																	   annuities,
//																	   floatingIndexMatrix,
//										                               bonds_0,
//										                               libors_init,
//											                           liborShifts,
//											                           approx2);
//
//
//		matrix_ newSwaptionMat = mktInfoHandler.chooseSwaptionMatrix(10); // Do calibration for tenor swap =  1Y to 10Y
//		matrix_ newSwapRateMat = mktInfoHandler.chooseSwapRates(10);
//		matrix_ newStrikes = newSwapRateMat;
//
//		//-- TODO : Compute annuities and pairs of indices
//
//
//		std::ofstream ofstr;
//		ofstr.open("E:\\SwaptionVolMatrix.xls");
//		for (size_t i = 0; i < h.size(); ++i)
//		{
//			for (size_t j = 0; j < h[i].size(); ++j)
//				ofstr << h[i][j] << "\t";
//
//			ofstr << endl;
//		}
//		ofstr << endl;
//		DateCreator::printMatrixOfIndices(ofstr,matrix_of_indices);
//		SwaptionCreator::print_swaptionMatrix(ofstr,swaptionMatrix2);
//
//		ofstr.close();
//
//		matrix_ weights(N+1,std::vector<double>(N+1)); 
//		matrix_ weights_maturity(N+1,std::vector<double>(N+1)); 
//		matrix_ weights_tenor(N+1,std::vector<double>(N+1)); 
//		matrix_ weights_maturity_2(N+1,std::vector<double>(N+1)); 
//		matrix_ weights_tenor_2(N+1,std::vector<double>(N+1)); 
//
//		for (size_t i = 1; i < N+1; ++i)
//		{
//			for (size_t j = 1; j <= i; ++j)
//			{
//				weights[i][j] = 1.;
//				weights_maturity[i][j] = 1.;
//				weights_tenor[i][j] = 1.;
//				weights_maturity_2[i][j] = 1.;
//				weights_tenor_2[i][j] = 1.;
//			}
//		}
//
//
//		matrix_ h_initialguess(N+1,std::vector<double>(N+1,0.));
//		
//		for (size_t i = 1; i < N+1; ++i)
//		{
//			for (size_t j = 1; j <= i; ++j)
//			{
//                h_initialguess[i][j] = h[i][j]*(1 + (rand()*0.3)/RAND_MAX);
//			}
//		}
//
//		Array startValues = vol.map_MatrixToArray(h_initialguess);
//		//NumericalMethods NM;
//		
//		//-- Create cost function 
//		SwaptionApproxCostFunction mycostfunction(swaptionMatrix2,
//			                                strikes,											
//											floatingIndexMatrix,
//										    swapRates,
//											annuities,
//											bonds_0,
//											libors_init,
//											liborShifts,
//											approx,
//											
//											weights,
//											weights_maturity,
//											weights_tenor,
//											weights_maturity_2,
//											weights_tenor_2);
//
//
//		cout << "Number of variables: " << nbVolalities << endl << endl;
//
//		ofstream outputFile;
//		outputFile.open("E:\\calibration_results.xls");
//
//		outputFile << "index libor/dates" << "\t";
//		for (size_t i = 0; i < N+1; ++i)
//			outputFile << tenorDates[i] << "\t";
//
//		outputFile << endl;
//
//		//-- Write initial vol matrix in xls file
//		outputFile << endl << "Libor vol matrix -- Initial guess" << endl;
//		for (size_t i = 0; i < N+1; ++i)
//		{
//			outputFile << "\t";
//			for (size_t j = 0; j < N+1; ++j)
//				outputFile << h_initialguess[i][j] << "\t";
//
//			outputFile << endl;
//		}
//		outputFile << endl;
//
//		outputFile << endl << "Libor Vol matrix -- Model Input" << endl;
//
//		//-- Save matrix h (input) in a xls file
//		vol.saveMatrix(outputFile); 
//
//		Calibration calibrator;
//		Array liborVolArray = calibrator.Calibrate(outputFile,mycostfunction,startValues);
//
//		
//		//-- Write swaption vol matrix in xls
//		outputFile << endl << "Swaption vol matrix (Rebonato)" << endl;
//		for (size_t i = 0; i < swaptionMatrix2.size(); ++i)
//		{
//			outputFile << "\t";
//			for (size_t j = 0; j < swaptionMatrix2[i].size(); ++j)
//			{
//				outputFile << swaptionMatrix2[i][j] << "\t";
//			}
//
//			outputFile << endl;
//		}
//		outputFile << endl;
//
//		
//
//		//------------------------------------------------------------------//
//		//               compute swaption vol after calibration             //
//		//------------------------------------------------------------------//
//
//		//matrix_ liborVolMatrix_output = mycostfunction.map_ArrayToMatrix(liborVolArray);
//
//		matrix_ liborVolMatrix_output = vol.map_ArrayToMatrix(liborVolArray);
//
//		PiecewiseConstantVolatility vol_calibrated(liborVolMatrix_output,tenorDates,nbFactors,N+1);
//
//		Approximation approx_calibrated(vol_calibrated,tenorDates);
//
//		//-- Create swaption matrix, as well as swap rates, strikes, annuities
//		matrix_ swaptionMatrix3 = SwaptionCreator::createSwaptionMatrix(matrix_of_indices,
//																	   floatPer, // = Libor tenor
//											                           floatingTenor_calibration,
//																	   fixingTenor_calibration,	
//																	   strikes,
//																	   swapRates,
//																	   annuities,
//																	   floatingIndexMatrix,
//										                               bonds_0,
//										                               libors_init,
//											                           liborShifts,
//											                           approx_calibrated);
//
//		outputFile << endl << "Swaption vol matrix (after calibration)" << endl;
//		for (size_t i = 0; i < swaptionMatrix3.size(); ++i)
//		{
//			outputFile << "\t";
//			for (size_t j = 0; j < swaptionMatrix3[i].size(); ++j)
//			{
//				outputFile << swaptionMatrix3[i][j] << "\t";
//			}
//			outputFile << endl;
//		}
//		outputFile << endl;
//		
//		outputFile << endl << "Relative errors (swaption vol)" << endl;
//		for (size_t i = 0; i < swaptionMatrix3.size(); ++i)
//		{
//			outputFile << "\t";
//			for (size_t j = 0; j < swaptionMatrix3[i].size(); ++j)
//			{
//				if (swaptionMatrix2[i][j] == 0.)
//					outputFile << 0. << "\t";
//				else
//				{
//					outputFile << (swaptionMatrix2[i][j]-swaptionMatrix3[i][j])/swaptionMatrix2[i][j] << "\t";
//				}
//			}
//
//			outputFile << endl;
//		}
//		outputFile << endl;
//
//		outputFile.close();
//
//	#pragma endregion
//
//	#pragma region TARN pricing
//
//		//double strike = 0.115;
//		//size_t exoLegTenor = 6;
//		//size_t liborLegTenor = 12;
//		//double target = 0.1;
//		//size_t indexStart = 2;
//		//size_t indexEnd = 5;
//		//
//		////-- Create a TARN
//		//Tarn tarn(strike,target,indexStart,indexEnd,liborLegTenor,exoLegTenor);
//
//		////-- Create the TARN pricer
//		//LmmTarnPricer tarnPricer(tarn,model);
//
//		////-- Call the MC pricing method
//		//tarnPricer.McTarnPrice(M,mcPrice,mcErr,libors_init,euler);
//
//		////model.printLiborMatrix();
//
//		//Real estimatedStdErr = 3*mcErr/sqrt((Real)M);
//		//Real lowerIc = mcPrice - estimatedStdErr;
//		//Real upperIc = mcPrice + estimatedStdErr;
//
//		//cout << "Number of MC simulations : " << M << endl << endl;
//		//cout << "----- Monte-Carlo price : " << mcPrice << endl << endl;
//		//cout << "Estimated standard error : " << estimatedStdErr << endl;
//		//cout << "99% confidence interval : " << "[" << lowerIc << " ; " << upperIc << "]" << " -- X = " << estimatedStdErr << endl;
//		//cout << endl << endl;
//
//	#pragma endregion
//
//	#pragma region Simulation tests
//
//		//matrix<Real> simulatedLibors(N+1,N+2,0.);
//		//matrix<Real> GaussianMatrix(nbFactors,N+1,0.);
//
//		////-- Fill the gaussian matrix
//		//numeric::ublas::vector<Real> G(nbFactors,0.);
//		//for (size_t k = 0; k < N+1; ++k) {
//		//	gen_normal(generator,G);
//		//	for (size_t i = 0; i < nbFactors; ++i)
//		//		GaussianMatrix(i,k) = G(i);
//		//}
//
//		//cout << "Gaussian matrix : " << endl;
//		//cout << GaussianMatrix << endl << endl;
//
//
//		////-- Initialize the libor matrix
//		//for (size_t i = 0; i < N+1; ++i)
//		//	simulatedLibors(i,0) = model.libor_0(i);
//
//		//liborSimul_terminal_euler(model,GaussianMatrix,simulatedLibors,covTensor);
//
//		//simulatedLibors.clear();
//		//for (size_t i = 0; i < N+1; ++i)
//		//	simulatedLibors(i,0) = model.libor_0(i);
//
//		//liborSimul_terminal_pc(model,GaussianMatrix,simulatedLibors,covTensor);
//
//		//simulatedLibors.clear();
//		//for (size_t i = 0; i < N+1; ++i)
//		//	simulatedLibors(i,0) = model.libor_0(i);
//
//		//liborSimul_spot_euler(model,GaussianMatrix,simulatedLibors,covTensor);
//
//		//simulatedLibors.clear();
//		//for (size_t i = 0; i < N+1; ++i)
//		//	simulatedLibors(i,0) = model.libor_0(i);
//
//		//liborSimul_spot_pc(model,GaussianMatrix,simulatedLibors,covTensor);
//
//	#pragma endregion
//
//	#pragma region Caplet pricing tests
//
//		//pricingCapletTest();
//
//	#pragma endregion
//
//		cin.ignore();
//	}
//	catch(const std::exception& ex)
//	{
//		cerr << ex.what() << endl;
//	}
//
	return 0;
}
