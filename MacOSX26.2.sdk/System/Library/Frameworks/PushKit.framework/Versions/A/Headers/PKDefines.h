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
/// Constants reflecting the push types you want to support.
///
/// ## Topics
///
/// ### Notification Types
///
/// - ``PushKit/PKPushTypeComplication``
/// - ``PushKit/PKPushTypeFileProvider``
/// - ``PushKit/PKPushTypeVoIP``
///
/// 
typedef NSString *PKPushType NS_STRING_ENUM;
