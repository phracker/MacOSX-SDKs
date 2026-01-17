//
//  GameplayKitBase.h
//  GameLogic
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>
#import <Availability.h>
#import <TargetConditionals.h>

//Exporting
#ifdef __cplusplus
#define GK_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define GK_EXPORT extern __attribute__((visibility ("default")))
#endif

//Availability
#define GK_BASE_AVAILABILITY NS_CLASS_AVAILABLE(10_11, 9_0)

#define GK_AVAILABLE __OSX_AVAILABLE_STARTING

//Inlining
#define GK_FORCE_INLINE __inline__ __attribute__((always_inline))

//Branch prediction
#define GK_LIKELY(x)    __builtin_expect(!!(x), 1)
#define GK_UNLIKELY(x)  __builtin_expect(!!(x), 0)
