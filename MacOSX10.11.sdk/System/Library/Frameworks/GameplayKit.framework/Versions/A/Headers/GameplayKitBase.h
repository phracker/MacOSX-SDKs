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

#ifdef __cplusplus
#define GK_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define GK_EXPORT extern __attribute__((visibility ("default")))
#endif

#define GK_BASE_AVAILABILITY NS_CLASS_AVAILABLE(10_11, 9_0)

#define GK_AVAILABLE __OSX_AVAILABLE_STARTING
