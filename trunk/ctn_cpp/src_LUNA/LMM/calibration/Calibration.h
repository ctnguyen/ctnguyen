#ifndef LMM_CALIBRATION_CALIBRATION_H
#define LMM_CALIBRATION_CALIBRATION_H
#pragma once

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <ql/math/optimization/endcriteria.hpp>
#include <ql/math/optimization/constraint.hpp>
#include <ql/math/optimization/problem.hpp>

//#include "TestCostFunction.h"
#include <LMM/calibration/SwaptionApproxCostFunction.h>


class Calibration 
{	
public:
	
	Calibration();
	
	Array Calibrate(ofstream& outputFile, SwaptionCostFunction& func, const Array& startValues);

	void saveCalibrationResults(ofstream& outputFile, const Array& calibrationResults);


	//-- Tests --//
	//void test_Minimizer(TestCostFunction&);
};

#endif /* LMM_CALIBRATION_CALIBRATION_H */