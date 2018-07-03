/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#include "greet.hpp"
#include <boost/python.hpp>
 
BOOST_PYTHON_MODULE(greet_ext)
{
    using namespace boost::python;
    def( "greet", greet );
}