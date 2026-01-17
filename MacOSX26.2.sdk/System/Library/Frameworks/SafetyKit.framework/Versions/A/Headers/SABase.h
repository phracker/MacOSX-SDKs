//
//  SABase.h
//  SafetyKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <os/availability.h>

#ifdef __cplusplus
#define SA_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define SA_EXTERN extern __attribute__((visibility("default")))
#endif

#define SA_EXPORT __attribute__((visibility ("default")))
