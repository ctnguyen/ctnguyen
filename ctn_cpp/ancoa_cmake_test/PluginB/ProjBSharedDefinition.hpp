#ifndef PROJBSharedDefinition_hpp
#define PROJBSharedDefinition_hpp

#ifdef WIN32
  #ifdef PROJB_LIB_API
    #define PROJB_LIB_EXPORT __declspec(dllexport)
  #else
    #ifdef NO_IMPORT
      #define PROJB_LIB_EXPORT
    #else
      #define PROJB_LIB_EXPORT __declspec(dllimport)
    #endif
  #endif
#else
  #define PROJB_LIB_EXPORT
#endif

#endif // PROJBSharedDefinition_hpp
