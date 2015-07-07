#ifndef PROJQtTestSharedDefinition_hpp
#define PROJQtTestSharedDefinition_hpp

#ifdef WIN32
  #ifdef PROJQtTest_LIB_API
    #define PROJQtTest_LIB_EXPORT __declspec(dllexport)
  #else
    #ifdef NO_IMPORT
      #define PROJQtTest_LIB_EXPORT
    #else
      #define PROJQtTest_LIB_EXPORT __declspec(dllimport)
    #endif
  #endif
#else
  #define PROJQtTest_LIB_EXPORT
#endif

#endif // PROJQtTestSharedDefinition_hpp
