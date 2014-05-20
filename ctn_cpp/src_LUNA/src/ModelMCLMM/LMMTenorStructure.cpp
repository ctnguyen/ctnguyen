#include <LMM/generic_path.h>
#include <LMM/helper/Printer.h>
#include <LMM/helper/EqualOperator.h>

#include <LMM/ModelMCLMM/LMMTenorStructure.h>

//! constructor
LMMTenorStructure::LMMTenorStructure(const Tenor&  tenorType, //! User should make sure the coherence.
									 const size_t horizonYear)
									 :tenorType_(tenorType)
{
	assert(horizonYear>1);

	if(!tenorType.isValidTenor())
		throw("Error: is not valid tenorType.");

	size_t nbMonthTenorType = tenorType.convertToMonth();

	//if(horizonYear%nbMonthTenorType!=0)
	//	throw("Error: cannot treat the case.");

	horizon_ = horizonYear*(12/nbMonthTenorType);		

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

//! equal operator: when modify the class, don't forget to adjust == operator
bool LMMTenorStructure::operator == (const LMMTenorStructure& lmmTenorStructure) const
{
	if(tenorType_ != lmmTenorStructure.tenorType_)
		return false;

	if(horizon_ != lmmTenorStructure.get_horizon())
		return false;

	if(vectorEqual(tenorDates_,lmmTenorStructure.get_tenorDate(), 1.0e-16))
		return false;

	if(vectorEqual(tenorDeltaT_,lmmTenorStructure.get_deltaT(), 1.0e-16))
		return false;

	return true;
}


void LMMTenorStructure::print(const std::string& filename) const
{
	//std::string fileName = "LMMTenorStructure.csv";
	std::string path = LMM::get_output_path() + filename;

	//seems a problem of shared ptr polymorphisms ... 
	PrintElement_PTR tenorType_print    = PrintElement_PTR(new ScalarPrintElement<std::string>("tenorType", tenorType_.name));
	PrintElement_PTR horizon_print      = PrintElement_PTR(new ScalarPrintElement<Name::indexInLMMTenorStructure>("horizon", horizon_));
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
