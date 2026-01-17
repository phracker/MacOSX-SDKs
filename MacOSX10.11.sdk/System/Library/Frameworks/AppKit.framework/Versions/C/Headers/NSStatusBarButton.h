/*
    NSStatusBarButton.h
    Application Kit
    Copyright (c) 1997-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSButton.h>

/*!
 * StatusBarButtons are the visual representation of NSStatusItems, and are primarily displayed on the right side of the menu bar.
 * When a template image is set as the \c image property of the status bar button, it is rendered with the correct menu bar style. This guarantees that the button will look correct in various button states and appearances (such as dark menu bar).
 */
NS_CLASS_AVAILABLE_MAC(10_10)
@interface NSStatusBarButton : NSButton {
@private
    id _statusBarButtonPrivate;
}

/// When YES the status bar icon has a disabled/off appearance while still being functional, such as allowing selection and actions. Defaults to NO.
@property BOOL appearsDisabled;

@end
