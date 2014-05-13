#pragma once

#include "McLmm.h"

class McTerminalLmm : public McLmm
{
public:			   
	McTerminalLmm(const Dispersion&   dispersion,
		const std::vector<double>&    shifts,
		const std::vector<double>&    liborsInitValue,
		RNGenerator_PTR               rnGenerator,
		MCSchemeType::MCSchemeType	  mcSchemeType);


	void simulateLMM();
	void computeNumeraires();

private:

	//! Backword simualtion
	void TerminalLmmModel_Euler();
	void TerminalLmmModel_Pc();  //! improve drift approximation: 2 time expensive as Euler
	void TerminalLmmModel_Ipc(); 

	//-- Tests
	void testTerminalNumeraires();
};

