#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIOrientation.h>)
//
//  UIOrientation.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIDeviceOrientation) {
    UIDeviceOrientationUnknown,
    UIDeviceOrientationPortrait,            // Device oriented vertically, home button on the bottom
    UIDeviceOrientationPortraitUpsideDown,  // Device oriented vertically, home button on the top
    UIDeviceOrientationLandscapeLeft,       // Device oriented horizontally, home button on the right
    UIDeviceOrientationLandscapeRight,      // Device oriented horizontally, home button on the left
    UIDeviceOrientationFaceUp,              // Device oriented flat, face up
    UIDeviceOrientationFaceDown             // Device oriented flat, face down
} API_UNAVAILABLE(tvos, watchos);

static inline BOOL UIDeviceOrientationIsPortrait(UIDeviceOrientation orientation)  API_UNAVAILABLE(tvos, visionos, watchos) {
    return ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown);
}

static inline BOOL UIDeviceOrientationIsLandscape(UIDeviceOrientation orientation)  API_UNAVAILABLE(tvos, visionos, watchos) {
    return ((orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight);
}

static inline __attribute__((always_inline)) BOOL UIDeviceOrientationIsFlat(UIDeviceOrientation orientation)  API_UNAVAILABLE(tvos, visionos, watchos) {
    return ((orientation) == UIDeviceOrientationFaceUp || (orientation) == UIDeviceOrientationFaceDown);
}

static inline __attribute__((always_inline)) BOOL UIDeviceOrientationIsValidInterfaceOrientation(UIDeviceOrientation orientation)  API_UNAVAILABLE(tvos, visionos, watchos) {
    return ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown || (orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight);
}

// Note that UIInterfaceOrientationLandscapeLeft is equal to UIDeviceOrientationLandscapeRight (and vice versa).
// This is because rotating the device to the left requires rotating the content to the right.
typedef NS_ENUM(NSInteger, UIInterfaceOrientation) {
    UIInterfaceOrientationUnknown            = UIDeviceOrientationUnknown,
    UIInterfaceOrientationPortrait           = UIDeviceOrientationPortrait,
    UIInterfaceOrientationPortraitUpsideDown = UIDeviceOrientationPortraitUpsideDown,
    UIInterfaceOrientationLandscapeLeft      = UIDeviceOrientationLandscapeRight,
    UIInterfaceOrientationLandscapeRight     = UIDeviceOrientationLandscapeLeft
} API_UNAVAILABLE(tvos, watchos);

typedef NS_OPTIONS(NSUInteger, UIInterfaceOrientationMask) {
    UIInterfaceOrientationMaskPortrait = (1 << UIInterfaceOrientationPortrait),
    UIInterfaceOrientationMaskLandscapeLeft = (1 << UIInterfaceOrientationLandscapeLeft),
    UIInterfaceOrientationMaskLandscapeRight = (1 << UIInterfaceOrientationLandscapeRight),
    UIInterfaceOrientationMaskPortraitUpsideDown = (1 << UIInterfaceOrientationPortraitUpsideDown),
    UIInterfaceOrientationMaskLandscape = (UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight),
    UIInterfaceOrientationMaskAll = (UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight | UIInterfaceOrientationMaskPortraitUpsideDown),
    UIInterfaceOrientationMaskAllButUpsideDown = (UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight),
} API_UNAVAILABLE(tvos, watchos);

static inline BOOL UIInterfaceOrientationIsPortrait(UIInterfaceOrientation orientation) API_UNAVAILABLE(tvos, watchos) {
    return ((orientation) == UIInterfaceOrientationPortrait || (orientation) == UIInterfaceOrientationPortraitUpsideDown);
}

static inline BOOL UIInterfaceOrientationIsLandscape(UIInterfaceOrientation orientation) API_UNAVAILABLE(tvos, watchos) {
    return ((orientation) == UIInterfaceOrientationLandscapeLeft || (orientation) == UIInterfaceOrientationLandscapeRight);
}

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIOrientation.h>
#endif
