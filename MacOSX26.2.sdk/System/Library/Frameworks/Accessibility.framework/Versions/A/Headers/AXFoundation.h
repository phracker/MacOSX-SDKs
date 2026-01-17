//
//  AXFoundation.h
//  Accessibility
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>

#if defined(__OBJC__) || defined(__swift__)
#import <Foundation/Foundation.h>
#endif

#ifndef AX_EXTERN
    #ifdef __cplusplus
        #define AX_EXTERN   extern "C" __attribute__((visibility("default")))
    #else
        #define AX_EXTERN   extern __attribute__((visibility("default")))
    #endif
#endif

#ifdef __swift__
    // This struct is not available in Objective-C. Its only purpose is to create a namespace for accessibility symbols in Swift.
typedef struct AccessibilitySettings { void *_reserved; } AccessibilitySettings;
#endif

