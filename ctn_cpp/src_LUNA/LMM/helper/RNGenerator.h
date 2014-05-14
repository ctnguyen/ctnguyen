#pragma once
#include <vector>
#include <boost/shared_ptr.hpp>

class RNGenerator 
{
protected:
	unsigned long seed_;
public:
	RNGenerator(unsigned long seed):seed_(seed){};
	virtual void generate(std::vector<double>& out_randomSequence) = 0; 

	//! getter/setter
	unsigned long getSeed() const {return seed_;}
	//virtual void resetSeed(unsigned long seedNew) =0;
	virtual void resetGeneratorToinitSeed()=0;
};

typedef boost::shared_ptr<RNGenerator> RNGenerator_PTR;