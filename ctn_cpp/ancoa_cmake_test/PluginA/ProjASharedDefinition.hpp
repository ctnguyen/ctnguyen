#ifndef PROJASharedDefinition_hpp
#define PROJASharedDefinition_hpp

#ifdef WIN32
  #ifdef PROJA_LIB_API
    #define PROJA_LIB_EXPORT __declspec(dllexport)
  #else
    #ifdef NO_IMPORT
      #define PROJA_LIB_EXPORT
    #else
      #define PROJA_LIB_EXPORT __declspec(dllimport)
    #endif
  #endif
#else
  #define PROJA_LIB_EXPORT
#endif

#endif // PROJASharedDefinition_hpp
