#ifndef PROJ2SharedDefinition_hpp
#define PROJ2SharedDefinition_hpp

#ifdef WIN32
  #ifdef PROJ2_LIB_API
    #define PROJ2_LIB_EXPORT __declspec(dllexport)
  #else
    #ifdef NO_IMPORT
      #define PROJ2_LIB_EXPORT
    #else
      #define PROJ2_LIB_EXPORT __declspec(dllimport)
    #endif
  #endif
#else
  #define PROJ2_LIB_EXPORT
#endif

#endif // PROJ2SharedDefinition_hpp
