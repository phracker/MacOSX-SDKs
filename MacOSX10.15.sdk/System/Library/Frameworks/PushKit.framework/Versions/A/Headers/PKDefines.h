//
//  PKDefines.h
//  PushKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#define PK_EXPORT           extern "C" __attribute__((visibility("default")))
#else
#define PK_EXPORT           extern __attribute__((visibility("default")))
#endif

typedef NSString *PKPushType NS_STRING_ENUM;
