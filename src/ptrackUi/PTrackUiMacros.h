#ifndef PTrackUiMacros_h
#define PTrackUiMacros_h

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define PTUI_API __attribute__ ((dllexport))
    #else
      #define PTUI_API __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define PTUI_API __attribute__ ((dllimport))
    #else
      #define PTUI_API __declspec(dllimport)
    #endif
  #endif
  #define PTUI_LOCAL
#else
  #if __GNUC__ >= 4
    #define PTUI_API __attribute__ ((visibility ("default")))
    #define PTUI_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define PTUI_API
    #define PTUI_LOCAL
  #endif
#endif

#endif
