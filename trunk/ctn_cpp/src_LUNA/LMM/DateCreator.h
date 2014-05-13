//#pragma once
//
//#include <cstring>
//#include <fstream>
//#include <vector>
//
//typedef std::vector<std::vector<double>> matrix_;
//typedef std::vector<std::vector<std::pair<double,double>>> matrix_pairOfYears;
//typedef std::vector<std::vector<std::pair<size_t,size_t>>> matrix_pairOfMonths;
//typedef std::vector<std::vector<std::pair<size_t,size_t>>> matrix_pairOfIndices;
//
//class DateCreator
//{
//public:
//	static std::vector<double> createLmmTenorDates(const std::vector<double>& lmmDeltaT);
//	static matrix_pairOfYears createSwaptionMatrixDates_Years(size_t size, double tenor);        // (xY,zY) (x=maturity, z=tenor)
//	static matrix_pairOfMonths convertSwaptionDates_YearsToMonths(const matrix_pairOfYears& matrixYears);   // (xY,zY) => (aM,bM)
//	static matrix_pairOfIndices convertSwaptionDates_MonthsToIndices(double tenor, const matrix_pairOfMonths& matrixMonths); // (aM,bM) => (start date-end date)
//
//	static void printMatrixOfYears(std::ofstream& outputFile, const matrix_pairOfYears&);
//	static void printMatrixOfMonths(std::ofstream& outputFile, const matrix_pairOfMonths&);
//	static void printMatrixOfIndices(std::ofstream& outputFile, const matrix_pairOfIndices&);
//
//	//---------------------------------------//
//	//                TESTS                  //
//	//---------------------------------------//
//
//	static void testMatrixDatesCreator();
//
//
//};
