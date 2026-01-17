//
//  CNCinematicBase.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>
#import <Availability.h>
#import <Foundation/NSObjCRuntime.h>

#ifdef __cplusplus
#define CN_CINEMATIC_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CN_CINEMATIC_EXTERN extern __attribute__((visibility ("default")))
#endif
