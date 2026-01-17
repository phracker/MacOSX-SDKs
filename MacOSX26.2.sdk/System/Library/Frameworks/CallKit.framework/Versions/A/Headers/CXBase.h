//
//  CXBase.h
//  CallKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
#define CX_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define CX_EXTERN extern __attribute__((visibility("default")))
#endif

#define CX_CLASS_AVAILABLE(...) CX_EXTERN API_AVAILABLE(__VA_ARGS__)

NS_ASSUME_NONNULL_END
