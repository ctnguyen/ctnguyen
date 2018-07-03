/****************************************************** *
*  Date             03/07/2018                          *
*  Creator          Chi Thanh NGUYEN                    *
*  Authors          chithanhnguyen.math@gmail.com       *
*                                                       *
*  Copyright (c) 2018 CTN Ltd. All rights reserved      *
*********************************************************/
#ifndef SharedDefineGreet_H
#define SharedDefineGreet_H

#include <sharedlibrary_defines.h>

#ifdef EXPORT_SHARED_GREET
#    define GREET_API EXPORT_DYNAMIC_LIBRARY
#else
#    define GREET_API IMPORT_DYNAMIC_LIBRARY
#endif

#endif /* SharedDefineGreet_H */
