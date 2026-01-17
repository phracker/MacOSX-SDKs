// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

#ifndef GK_EXTERN
#ifdef __cplusplus
#define GK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define GK_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

#ifndef GK_EXTERN_WEAK
#define GK_EXTERN_WEAK  GK_EXTERN __attribute__((weak_import))
#endif

typedef NSDictionary<NSString *, id> GKMatchProperties API_AVAILABLE(ios(17.2), macos(14.2), watchos(10.2), tvos(17.2), visionos(1.1));
