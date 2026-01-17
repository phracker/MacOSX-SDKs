/*
 *  EventKitUIDefines.h
 *  EventKitUI
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include <Availability.h>

#ifdef __cplusplus
#define EVENTKITUI_EXTERN               extern "C" __attribute__((visibility ("default")))
#else
#define EVENTKITUI_EXTERN               extern __attribute__((visibility ("default")))
#endif

#define EVENTKITUI_CLASS_AVAILABLE(_iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, _iphoneIntro)

#ifndef EKUI_HAS_HEADER
#if defined(__has_include)
#define EKUI_HAS_HEADER(include_path) (__has_include(include_path))
#else
#define EKUI_HAS_HEADER(include_path) (0)
#endif
#endif

#ifndef EKUI_IS_IOS
#if defined(TARGET_OS_IOS)
#define EKUI_IS_IOS (TARGET_OS_IOS)
#else
#define EKUI_IS_IOS (0)
#endif
#endif

#ifndef EKUI_IS_SIMULATOR
#if defined(TARGET_OS_SIMULATOR)
#define EKUI_IS_SIMULATOR (TARGET_OS_SIMULATOR)
#else
#define EKUI_IS_SIMULATOR (0)
#endif
#endif


// Macro to enable extensions to use classes / protocols starting on a certain iOS version.

#if defined(__has_feature)
  #if __has_feature(attribute_availability_app_extension)
    #define __EKUI_IOS_EXTENSION_AVAILABLE(_vers,_msg)  __OS_AVAILABILITY_MSG(ios_app_extension,introduced=_vers,_msg)
  #else
    #define __EKUI_IOS_EXTENSION_AVAILABLE(_vers,_msg)
  #endif
#else
    #define __EKUI_IOS_EXTENSION_AVAILABLE(_vers,_msg)
#endif

#define EKUI_EXTENSION_AVAILABLE_IOS(_vers, _msg)  __EKUI_IOS_EXTENSION_AVAILABLE(_vers, _msg)
