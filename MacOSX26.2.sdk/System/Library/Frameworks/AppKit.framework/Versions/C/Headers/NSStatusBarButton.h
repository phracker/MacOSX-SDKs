/*
    NSStatusBarButton.h
    Application Kit
    Copyright (c) 1997-2024, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSButton.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

/// Status bar buttons are the visual representation of `NSStatusItem`s, and are primarily displayed on the right side of the menu bar.
/// When a template image is set as the `image` property of the status bar button, it is rendered with the correct menu bar style. This guarantees that the button will look correct in various button states and appearances (such as dark menu bar).
API_AVAILABLE(macos(10.10))
@interface NSStatusBarButton : NSButton

/// If `YES`, the status bar icon has a disabled/off appearance while still being functional, such as allowing selection and actions. Defaults to `NO`.
@property BOOL appearsDisabled;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
