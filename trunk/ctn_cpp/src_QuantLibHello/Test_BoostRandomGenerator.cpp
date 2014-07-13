#include <iostream>
#include <ctime>
#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/bernoulli_distribution.hpp>

/*! This small program test how to use timer with high resolution and
 *  use this timer for generating random number
 *
 *  This generate a multiplicative noise, can be helpful when one wish to perturbe a real numbers vectors.
 */
int main(int, char* []) {

	double perturbe_noise = 0.2;
	size_t nbNumber = 10;

	boost::random::mt19937 gen;

	{
		boost::random::uniform_real_distribution<> dist(1-perturbe_noise,1+perturbe_noise);
		boost::variate_generator<boost::mt19937&,boost::random::uniform_real_distribution<> > rng_uniform(gen, dist);
		rng_uniform.engine().seed( static_cast<unsigned int>(std::time(0)) );

    	std::vector<double> uniform_noise_vector( nbNumber );
    	for(size_t i=0;i<nbNumber;++i){   uniform_noise_vector[i] = rng_uniform(); }

    	for(size_t i=nbNumber;i>0;--i)
    	{
    		std::cout<<"uniform_noise_vector["<<i-1<<"]	"<<uniform_noise_vector[i-1]<<std::endl;
    	}
    }

	{
		boost::random::bernoulli_distribution<> bernouilli_dist(0.5);
		boost::variate_generator<boost::mt19937&,boost::random::bernoulli_distribution<> > rng_bernouilli(gen, bernouilli_dist);
		rng_bernouilli.engine().seed( static_cast<unsigned int>(std::time(0)) );

    	std::vector<double> bernouilli_noise_vector( nbNumber );
    	for(size_t i=0;i<nbNumber;++i){   bernouilli_noise_vector[i] = 1.+ perturbe_noise*(2.*rng_bernouilli() - 1.); }

    	for(size_t i=nbNumber;i>0;--i)
    	{
    		std::cout<<"bernouilli_noise_vector["<<i-1<<"]	"<<bernouilli_noise_vector[i-1]<<std::endl;
    	}
    }


	return 0;
}

