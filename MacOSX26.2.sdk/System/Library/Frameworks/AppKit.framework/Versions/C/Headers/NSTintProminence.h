/*
        NSTintProminence.h
        Application Kit
        Copyright (c) 2025, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

/*! Controls how strongly the tint color applies in a view.
 *
 *  A tint prominence of `primary` will use the app's tint color with full
 *  saturation and brightness, while `secondary` will apply it more subtly.
 *  Using `none` gives an untinted appearance.
 */
typedef NS_ENUM(NSInteger, NSTintProminence) {
    NSTintProminenceAutomatic = 0,
    NSTintProminenceNone,
    NSTintProminencePrimary,
    NSTintProminenceSecondary,
} API_AVAILABLE(macos(26.0));

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
