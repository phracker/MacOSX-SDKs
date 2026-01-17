/*
 *  CMAvailability.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */
#ifndef CMAvailability_h
#define CMAvailability_h

#import <Availability.h>
#import <os/availability.h>

#ifdef __cplusplus
#define CM_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CM_EXTERN extern __attribute__((visibility ("default")))
#endif

#define COREMOTION_EXPORT __attribute__((visibility ("default")))

#endif // CMAvailability_h
