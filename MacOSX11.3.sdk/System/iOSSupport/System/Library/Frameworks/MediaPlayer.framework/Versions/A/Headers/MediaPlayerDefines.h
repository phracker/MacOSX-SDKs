//
//  MediaPlayerDefines.h
//  MediaPlayer
//
//  Copyright 2008-2019 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <TargetConditionals.h>

#ifdef __cplusplus
#define _MP_EXTERN extern "C"
#else
#define _MP_EXTERN extern
#endif
#define _MP_VISIBLE                                 __attribute__((visibility("default")))
#define _MP_VISIBLE_BEGIN                           _Pragma("(clang attribute _MP_VISIBLE)")
#define _MP_HIDDEN                                  __attribute__((visibility("hidden")))

#ifndef MP_EXTERN
#define MP_EXTERN                                   _MP_EXTERN _MP_VISIBLE
#endif

#pragma mark - Availability

#define MP_API(...)                                 __API_AVAILABLE(__VA_ARGS__) _MP_VISIBLE
#define MP_API_BEGIN(...)                           __API_AVAILABLE_BEGIN(__VA_ARGS__) _MP_VISIBLE_BEGIN
#define MP_API_END                                  __API_AVAILABLE_END

#define MP_UNAVAILABLE(...)                         __API_UNAVAILABLE(__VA_ARGS__)
#define MP_UNAVAILABLE_BEGIN(...)                   __API_UNAVAILABLE_BEGIN(__VA_ARGS__)
#define MP_UNAVAILABLE_END                          __API_UNAVAILABLE_END

#define MP_DEPRECATED(...)                          __API_DEPRECATED(__VA_ARGS__) _MP_VISIBLE
#define MP_DEPRECATED_BEGIN(...)                    __API_DEPRECATED_BEGIN(__VA_ARGS__) _MP_VISIBLE_BEGIN
#define MP_DEPRECATED_END                           __API_DEPRECATED_END

#define MP_DEPRECATED_WITH_REPLACEMENT(...)         __API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)
#define MP_DEPRECATED_WITH_REPLACEMENT_BEGIN(...)   __API_DEPRECATED_WITH_REPLACEMENT_BEGIN(__VA_ARGS__)
#define MP_DEPRECATED_WITH_REPLACEMENT_END          __API_DEPRECATED_WITH_REPLACEMENT_END

#pragma mark - Framework Availability

#define MP_HAS_UIKIT                                __has_include(<UIKit/UIView.h>)

#pragma mark - Utility

#define MP_INIT_UNAVAILABLE \
    + (instancetype)new NS_UNAVAILABLE; \
    - (instancetype)init NS_UNAVAILABLE;
