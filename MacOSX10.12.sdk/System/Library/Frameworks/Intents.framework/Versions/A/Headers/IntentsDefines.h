//
//  IntentsDefines.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define INTENTS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define INTENTS_EXTERN extern __attribute__((visibility ("default")))
#endif
