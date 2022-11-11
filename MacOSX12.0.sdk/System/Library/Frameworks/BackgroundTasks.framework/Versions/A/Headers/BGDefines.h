//
//  BGDefines.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#define BG_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define BG_EXTERN extern __attribute__((visibility("default")))
#endif

