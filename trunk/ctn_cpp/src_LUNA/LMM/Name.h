#ifndef LMM_NAME_H
#define LMM_NAME_H
#pragma once

/*
namespace Name
{
	typedef size_t NumberOfMonth;
	typedef size_t indexInLMMTenorStructure;
}*/

namespace OptionType
{
	enum OptionType {CALL, PUT};
}

namespace LMM
{
	typedef size_t Index;

	// Store a couple of years
	typedef std::vector<std::vector<std::pair<double,double> > > Matrix_PairOfYears;
}

#endif /* LMM_NAME_H */