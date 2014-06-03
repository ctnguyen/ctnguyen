//#include <LMM/ModelMCLMM/LMMTenorStructure.h>
#include <LMM/helper/LMMTenorStructure.h>

#include <LMM/generic_path.h>
#include <LMM/helper/Printer.h>
#include <LMM/helper/EqualOperator.h>

//! constructor
LMMTenorStructure::LMMTenorStructure(const Tenor&  tenorType, const size_t horizonYear)
: tenorType_(tenorType)
{
	assert(horizonYear>1);

	if(!tenorType.isValidTenor()) throw("Error: is not valid tenorType.");

	size_t nbMonthTenorType = tenorType.convertToMonth();
	
	horizon_ = horizonYear*(12/nbMonthTenorType);	//ctntodo potential bug when 2 years, 9M	

	double tenorDateStep = tenorType.convertToYear();

	tenorDates_  = std::vector<double>(horizon_+2); // Ti, i=[0,...,N+1]
	for(size_t i=0; i<tenorDates_.size(); ++i)
	{
		tenorDates_[i] = i*tenorDateStep;
	}

	//! YY Note: for the moment it's constant, but may change latter
	tenorDeltaT_ = std::vector<double>(horizon_+1,0.0);
	for(size_t i=0; i<tenorDeltaT_.size(); ++i)
	{
		tenorDeltaT_[i] = tenorDates_[i+1] - tenorDates_[i];
	}		
}


const Tenor& LMMTenorStructure::get_tenorType() const {return tenorType_;}

LMM::Index LMMTenorStructure::get_horizon() const { return horizon_; }

const double&              LMMTenorStructure::get_deltaT(size_t index) const { return tenorDeltaT_[index];}
const std::vector<double>& LMMTenorStructure::get_deltaT(            ) const {return tenorDeltaT_;        }

const double&              LMMTenorStructure::get_tenorDate(size_t index) const { return tenorDates_[index]; }
const std::vector<double>& LMMTenorStructure::get_tenorDate(            ) const { return tenorDates_;        }


//! equal operator: when modify the class, don't forget to adjust == operator
bool LMMTenorStructure::operator == (const LMMTenorStructure& lmmTenorStructure) const
{
	if(horizon_ != lmmTenorStructure.get_horizon())	return false;

	if(tenorType_ != lmmTenorStructure.tenorType_) return false;

	if(!vectorEqual(tenorDates_,lmmTenorStructure.get_tenorDate(), 1.0e-16)) return false;

	if(!vectorEqual(tenorDeltaT_,lmmTenorStructure.get_deltaT(), 1.0e-16)) return false;

	return true;
}

bool LMMTenorStructure::operator!=(const LMMTenorStructure& lmmTenorStructure) const
{
	if(horizon_ != lmmTenorStructure.get_horizon())	return true;

	if(tenorType_ != lmmTenorStructure.tenorType_) return true;

	if(!vectorEqual(tenorDates_,lmmTenorStructure.get_tenorDate(), 1.0e-16)) return true;

	if(!vectorEqual(tenorDeltaT_,lmmTenorStructure.get_deltaT(), 1.0e-16)) return true;

	return false;
}



void LMMTenorStructure::print(const std::string& filename) const
{
	std::string path = LMM::get_output_path() + filename;

	//seems a problem of shared ptr polymorphisms ... 
	PrintElement_PTR tenorType_print    = PrintElement_PTR(new ScalarPrintElement<std::string>( "tenorType", std::string(tenorType_.name) ) );
	PrintElement_PTR horizon_print      = PrintElement_PTR(new ScalarPrintElement<LMM::Index>("horizon", horizon_));
	PrintElement_PTR tenorDates_print   = PrintElement_PTR(new VectorPrintElement<std::vector<double> >("tenorDates" ,  tenorDates_ ) );
	PrintElement_PTR tenorDeltaT_print  = PrintElement_PTR(new VectorPrintElement<std::vector<double> >( "tenorDeltaT" ,  tenorDeltaT_ ) );

    std::vector<PrintElement_PTR> elements_print;
	elements_print.push_back(tenorType_print);
	elements_print.push_back(horizon_print);
	elements_print.push_back(tenorDates_print);
	elements_print.push_back(tenorDeltaT_print);

	Printer printer(path, elements_print);
	printer.print();
}
