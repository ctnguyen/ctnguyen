#ifndef BaseLibASymbols_hpp
#define BaseLibASymbols_hpp

#ifdef WIN32
    #ifdef BaseLibA_EXPORT
        #define BaseLibA_API __declspec(dllexport)
    #else
        #define BaseLibA_API __declspec(dllimport)
    #endif
#else
  #define BaseLibA_API
#endif

#endif // BaseLibASymbols_hpp
