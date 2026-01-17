//
//  GameplayKitBase.h
//  GameplayKit
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

//Visibility
#define GK_DEFAULT __attribute__((visibility ("default")))

//Availability
#define GK_BASE_AVAILABILITY NS_CLASS_AVAILABLE(10_11, 9_0)
#define GK_BASE_AVAILABILITY_2 NS_CLASS_AVAILABLE(10_12, 10_0)
#define GK_BASE_AVAILABILITY_3 NS_CLASS_AVAILABLE(10_13, 11_0)

#define GK_AVAILABLE __OSX_AVAILABLE_STARTING

//Inlining
#define GK_FORCE_INLINE __inline__ __attribute__((always_inline))

//Branch prediction
#define GK_LIKELY(x)    __builtin_expect(!!(x), 1)
#define GK_UNLIKELY(x)  __builtin_expect(!!(x), 0)

// Attribute annotation to parse properties from GKComponent derived component classes
#define GKInspectable __attribute__((annotate("gk_inspectable")))
