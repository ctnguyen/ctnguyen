/************************************************
*     Mini Porject for cmake test full feature  *
*     Use of cmake, cTest, cPack, Dashboard     *
*     @authors Chi Thanh NGUYEN                 *
*     contact chithanhnguyen.math@gmail.com     *
*************************************************/
/**
 *	@file Proj1/Proj1.hpp
 *	@date June 2015
 */

#ifndef BASELIBB_HPP
#define BASELIBB_HPP

#include <BaseLibB/BaseLibBSymbols.hpp>
#include <string>

class BaseLibB_API BaseLibB
{
public:

	BaseLibB();
    
    virtual std::string name() const;

	~BaseLibB();
};

#endif /* BASELIBB_HPP */
