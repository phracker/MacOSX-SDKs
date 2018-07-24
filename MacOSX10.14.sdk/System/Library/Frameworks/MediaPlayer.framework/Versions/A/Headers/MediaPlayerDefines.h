//
//  MediaPlayerDefines.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Availability.h>
#import <TargetConditionals.h>

#ifdef __cplusplus
#define MP_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define MP_EXTERN extern __attribute__((visibility ("default")))
#endif

#define MP_API(...) __API_AVAILABLE(__VA_ARGS__)
#define MP_DEPRECATED(...) __API_DEPRECATED(__VA_ARGS__)
#define MP_UNAVAILABLE(...) __API_UNAVAILABLE(__VA_ARGS__)
#define MP_DEPRECATED_WITH_REPLACEMENT(...) __API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)

#pragma mark - Prohibited

#define __MP_PROHIBITED_PLATFORM_macos macos,unavailable
#define __MP_PROHIBITED_PLATFORM_macosx macosx,unavailable
#define __MP_PROHIBITED_PLATFORM_ios ios,unavailable
#define __MP_PROHIBITED_PLATFORM_watchos watchos,unavailable
#define __MP_PROHIBITED_PLATFORM_tvos tvos,unavailable


#if __has_include(<AvailabilityProhibitedInternal.h>)
#define __MP_P(x)
#else
#define __MP_P(x) __attribute__((availability(__MP_PROHIBITED_PLATFORM_##x)))
#endif

#define __MP_PROHIBITED1(x) __MP_P(x)
#define __MP_PROHIBITED2(x,y) __MP_P(x) __MP_P(y)
#define __MP_PROHIBITED3(x,y,z) __MP_PROHIBITED2(x,y) __MP_P(z)
#define __MP_PROHIBITED4(x,y,z,t) __MP_PROHIBITED3(x,y) __MP_P(b)
#define __MP_PROHIBITED_GET_MACRO(_1,_2,_3,_4,NAME,...) NAME

#define MP_PROHIBITED(...) __MP_PROHIBITED_GET_MACRO(__VA_ARGS__,__MP_PROHIBITED4,__MP_PROHIBITED3,__MP_PROHIBITED2,__MP_PROHIBITED1)(__VA_ARGS__)

#define MP_HAS_UIVIEW               __has_include(<UIKit/UIView.h>)
#define MP_HAS_AVMEDIASELECTION     __has_include(<AVFoundation/AVMediaSelection.h>)
