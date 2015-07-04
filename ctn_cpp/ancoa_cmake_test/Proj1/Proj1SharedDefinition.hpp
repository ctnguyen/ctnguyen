#ifndef Proj1SharedDefinition_hpp
#define Proj1SharedDefinition_hpp

#ifdef WIN32
  #ifdef PROJ1_LIB_API
    #define PROJ1_LIB_EXPORT __declspec(dllexport)
  #else
    #ifdef NO_IMPORT
      #define PROJ1_LIB_EXPORT
    #else
      #define PROJ1_LIB_EXPORT __declspec(dllimport)
    #endif
  #endif
#else
  #define PROJ1_LIB_EXPORT
#endif

#endif // Proj1SharedDefinition_hpp
