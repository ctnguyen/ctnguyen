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

#ifndef BASELIBA_HPP
#define BASELIBA_HPP

#include <BaseLibA/BaseLibASymbols.hpp>
#include <string>

class BaseLibA_API BaseLibA
{
public:

	BaseLibA();

    virtual std::string name() const;

	~BaseLibA();
};

#endif /* BASELIBA_HPP */
