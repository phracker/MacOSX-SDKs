//
//  SWDefines.h
//  SWDefines
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#ifdef __cplusplus
#define SW_EXTERN        extern "C" __attribute__((visibility ("default")))
#define SW_HIDDEN        extern "C" __attribute__((visibility ("hidden")))
#else
#define SW_EXTERN            extern __attribute__((visibility ("default")))
#define SW_HIDDEN            extern __attribute__((visibility ("hidden")))
#endif
