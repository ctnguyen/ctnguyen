#ifndef BaseLibBSymbols_hpp
#define BaseLibBSymbols_hpp

#ifdef WIN32
    #ifdef BaseLibB_EXPORT
        #define BaseLibB_API __declspec(dllexport)
    #else
        #define BaseLibB_API __declspec(dllimport)
    #endif
#else
  #define BaseLibB_API
#endif

#endif // BaseLibBSymbols_hpp
