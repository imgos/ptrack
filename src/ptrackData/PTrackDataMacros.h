#ifndef PTrackDataMacros_h
#define PTrackDataMacros_h

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define PTDATA_API __attribute__ ((dllexport))
    #else
      #define PTDATA_API __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define PTDATA_API __attribute__ ((dllimport))
    #else
      #define PTDATA_API __declspec(dllimport)
    #endif
  #endif
  #define PTDATA_LOCAL
#else
  #if __GNUC__ >= 4
    #define PTDATA_API __attribute__ ((visibility ("default")))
    #define PTDATA_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define PTDATA_API
    #define PTDATA_LOCAL
  #endif
#endif

#endif
