#ifndef HEXAPOD_INTERFACES__VISIBILITY_CONTROL_H_
#define HEXAPOD_INTERFACES__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define HEXAPOD_INTERFACES_EXPORT __attribute__ ((dllexport))
    #define HEXAPOD_INTERFACES_IMPORT __attribute__ ((dllimport))
  #else
    #define HEXAPOD_INTERFACES_EXPORT __declspec(dllexport)
    #define HEXAPOD_INTERFACES_IMPORT __declspec(dllimport)
  #endif
  #ifdef HEXAPOD_INTERFACES_BUILDING_LIBRARY
    #define HEXAPOD_INTERFACES_PUBLIC HEXAPOD_INTERFACES_EXPORT
  #else
    #define HEXAPOD_INTERFACES_PUBLIC HEXAPOD_INTERFACES_IMPORT
  #endif
  #define HEXAPOD_INTERFACES_PUBLIC_TYPE HEXAPOD_INTERFACES_PUBLIC
  #define HEXAPOD_INTERFACES_LOCAL
#else
  #define HEXAPOD_INTERFACES_EXPORT __attribute__ ((visibility("default")))
  #define HEXAPOD_INTERFACES_IMPORT
  #if __GNUC__ >= 4
    #define HEXAPOD_INTERFACES_PUBLIC __attribute__ ((visibility("default")))
    #define HEXAPOD_INTERFACES_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define HEXAPOD_INTERFACES_PUBLIC
    #define HEXAPOD_INTERFACES_LOCAL
  #endif
  #define HEXAPOD_INTERFACES_PUBLIC_TYPE
#endif
#endif  // HEXAPOD_INTERFACES__VISIBILITY_CONTROL_H_
// Generated 12-Jul-2025 23:04:51
 