//
//  MediaPlayerDefines.h
//  MediaPlayer
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef MP_DEFINES
#define MP_DEFINES

#import <Availability.h>
#import <TargetConditionals.h>

#ifdef __cplusplus
#define _MP_EXTERN extern "C"
#else
#define _MP_EXTERN extern
#endif
#define _MP_VISIBLE                                 __attribute__((visibility("default")))
#define _MP_HIDDEN                                  __attribute__((visibility("hidden")))

#ifndef MP_EXTERN
#define MP_EXTERN                                   _MP_EXTERN _MP_VISIBLE
#endif

#pragma mark - Availability

#define MP_API(...)                                 __API_AVAILABLE(__VA_ARGS__) _MP_VISIBLE
#define MP_API_BEGIN                                __API_AVAILABLE_BEGIN
#define MP_API_END                                  __API_AVAILABLE_END

#define MP_UNAVAILABLE(...)                         __API_UNAVAILABLE(__VA_ARGS__)
#define MP_UNAVAILABLE_BEGIN(...)                   __API_UNAVAILABLE_BEGIN(__VA_ARGS__)
#define MP_UNAVAILABLE_END                          __API_UNAVAILABLE_END

#define MP_DEPRECATED(...)                          __API_DEPRECATED(__VA_ARGS__) _MP_VISIBLE
#define MP_DEPRECATED_BEGIN                         __API_DEPRECATED_BEGIN
#define MP_DEPRECATED_END                           __API_DEPRECATED_END

#define MP_DEPRECATED_WITH_REPLACEMENT(...)         __API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)
#define MP_DEPRECATED_WITH_REPLACEMENT_BEGIN(...)   __API_DEPRECATED_WITH_REPLACEMENT_BEGIN(__VA_ARGS__)
#define MP_DEPRECATED_WITH_REPLACEMENT_END          __API_DEPRECATED_WITH_REPLACEMENT_END

#define MP_FALLTHROUGH __attribute__((fallthrough))
#define MP_TYPE_PROTOCOL __attribute((objc_non_runtime_protocol))
#define MP_COMPLETION __attribute__((called_once))
#define MP_OVERLOAD __attribute__((overloadable))
#define MP_FINAL_CLASS __attribute__((objc_subclassing_restricted))

#pragma mark - Utility

#define __MP_OVERRIDE_HAS(FRAMEWORK)                ((defined(MP_HAS_##FRAMEWORK) && MP_HAS_##FRAMEWORK) || (!defined(MP_HAS_##FRAMEWORK) && 1))
#define MP_HAS(FRAMEWORK)                           __has_include(<FRAMEWORK/FRAMEWORK.h>) && __MP_OVERRIDE_HAS(FRAMEWORK)
#define MP_HAS_HEADER(FRAMEWORK, HEADER)            __has_include(<FRAMEWORK/HEADER>)


#if defined(__OBJC__) && __OBJC__

#define MP_INIT_UNAVAILABLE \
    + (instancetype)new NS_UNAVAILABLE; \
    - (instancetype)init NS_UNAVAILABLE;

#endif



#pragma mark - Additions

#if __has_include(<MediaPlayer/MediaPlayerDefines_Additions.h>)
#import <MediaPlayer/MediaPlayerDefines_Additions.h>
#endif

#endif
