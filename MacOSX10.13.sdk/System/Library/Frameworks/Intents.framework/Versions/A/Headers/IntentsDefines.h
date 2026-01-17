//
//  IntentsDefines.h
//  Intents
//
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define INTENTS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define INTENTS_EXTERN extern __attribute__((visibility ("default")))
#endif
