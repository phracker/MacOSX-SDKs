//
//  VZDefines.h
//  Virtualization
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

#ifdef __cplusplus
#define VZ_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#define VZ_EXPORT extern __attribute__((visibility ("default")))
#endif
