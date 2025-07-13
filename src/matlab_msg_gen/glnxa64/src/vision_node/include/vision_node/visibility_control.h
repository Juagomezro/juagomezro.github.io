#ifndef VISION_NODE__VISIBILITY_CONTROL_H_
#define VISION_NODE__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define VISION_NODE_EXPORT __attribute__ ((dllexport))
    #define VISION_NODE_IMPORT __attribute__ ((dllimport))
  #else
    #define VISION_NODE_EXPORT __declspec(dllexport)
    #define VISION_NODE_IMPORT __declspec(dllimport)
  #endif
  #ifdef VISION_NODE_BUILDING_LIBRARY
    #define VISION_NODE_PUBLIC VISION_NODE_EXPORT
  #else
    #define VISION_NODE_PUBLIC VISION_NODE_IMPORT
  #endif
  #define VISION_NODE_PUBLIC_TYPE VISION_NODE_PUBLIC
  #define VISION_NODE_LOCAL
#else
  #define VISION_NODE_EXPORT __attribute__ ((visibility("default")))
  #define VISION_NODE_IMPORT
  #if __GNUC__ >= 4
    #define VISION_NODE_PUBLIC __attribute__ ((visibility("default")))
    #define VISION_NODE_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define VISION_NODE_PUBLIC
    #define VISION_NODE_LOCAL
  #endif
  #define VISION_NODE_PUBLIC_TYPE
#endif
#endif  // VISION_NODE__VISIBILITY_CONTROL_H_
// Generated 12-Jul-2025 23:04:52
 