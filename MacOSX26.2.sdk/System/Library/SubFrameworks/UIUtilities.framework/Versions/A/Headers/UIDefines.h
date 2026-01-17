//
//  UIDefines.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#ifdef __cplusplus
#define UIKIT_EXTERN       extern "C" __attribute__((visibility ("default")))
#else
#define UIKIT_EXTERN           extern __attribute__((visibility ("default")))
#endif

#define UIKIT_STATIC_INLINE    static inline

#if !defined(UIKIT_EXTERN_C_BEGIN) && !defined(UIKIT_EXTERN_C_END)
    #ifdef __cplusplus
        #define UIKIT_EXTERN_C_BEGIN extern "C" {
        #define UIKIT_EXTERN_C_END }
    #else
        #define UIKIT_EXTERN_C_BEGIN
        #define UIKIT_EXTERN_C_END
    #endif
#endif
