#include <iostream>
#include "QMcGenerator.h"


QMcGenerator::QMcGenerator(unsigned long qmcSeed, size_t sequence_size, size_t skipRank) 
	: RNGenerator(qmcSeed),
	  sequence_size_(sequence_size),
	  skipRank_(skipRank),
	  sobol_(sequence_size,qmcSeed),
	  generator_(sobol_)

{
	sobol_.skipTo(skipRank_);
	generator_ = InverseCumulativeRsg<SobolRsg,InverseCumulativeNormal>(sobol_);
}


void QMcGenerator::generate(std::vector<double>& out_randomSequence) 
{
	throw("Error: what a shit why use sequence_size other than real size for generating ?");
	for (size_t i = 0; i < sequence_size_; ++i)
	{
		out_randomSequence.push_back(generator_.nextSequence().value[i]);
	}
}
	
//double QMcGenerator::getSeed() {return qmcSeed_;}
size_t QMcGenerator::getSequenceSize() {return sequence_size_;}

//void QMcGenerator::setSeed(unsigned long seed) {qmcSeed_ = seed;}
void QMcGenerator::setSequenceSize(size_t size) {sequence_size_ = size;}



//----------------------------------------------------------------------------//
//                                                                            //
//                                    TESTS                                   //
//                                                                            //
//----------------------------------------------------------------------------//
//
//void testSobolLsdGeneration()
//{
//	std::vector<double> random_sequence;
//	generate(random_sequence);
//
//	std::cout << "-- Sobol LDS generation --" << std::endl;
//	for each (double rand_num in random_sequence)
//		std::cout << rand_num << " ";
//	
//	std::cout << std::endl;
//}
//
//void test2()
//{
//	SobolRsg sobol(20,1); //-- Create a 20 dim sobol sequence generator
//	sobol.skipTo(4096); //-- Skip the first sequences as they are badly distributed...
//	std::vector<double> point = sobol.nextSequence().value;
//	std::cout << "Sobol sequence dimension: " << point.size() << std::endl;
//	std::cout << "Sobol sequence: " << std::endl;
//	for each (double num in point)
//		std::cout << num << " ";
//
//	std::cout << std::endl << std::endl;
//
//	//-- Fill a vector with a normally distributed sequence, obtained from sobol generator
//	std::vector<double> rand_seq;
//	InverseCumulativeRsg<SobolRsg,InverseCumulativeNormal> generator(sobol);
//	rand_seq = generator.nextSequence().value;
//	std::cout << "Normally distributed sequence: " << std::endl;
//	for each (double num in rand_seq)
//		std::cout << num << " ";
//
//	std::cout << std::endl << std::endl;
//}