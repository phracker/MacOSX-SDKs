//
//  VideoSubscriberAccountDefines.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <Foundation/NSObjCRuntime.h>

#define VS_EXPORT __attribute__((visibility ("default")))
#define VS_INTERNAL_EXPORT __attribute__((visibility("internal")))

#ifdef __cplusplus
#define VS_EXTERN extern "C" VS_EXPORT
#define VS_INTERNAL_EXTERN extern "C" VS_INTERNAL_EXPORT
#else
#define VS_EXTERN extern VS_EXPORT
#define VS_INTERNAL_EXTERN extern VS_INTERNAL_EXPORT
#endif
