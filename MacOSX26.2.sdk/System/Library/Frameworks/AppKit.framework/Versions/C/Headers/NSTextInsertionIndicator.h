/*
        NSTextInsertionIndicator.h
        Application Kit
        Copyright (c) 2023-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKit.h>

APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST
NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, NSTextInsertionIndicatorDisplayMode) {
    NSTextInsertionIndicatorDisplayModeAutomatic = 0,  // Automatically stops and starts blinking during typing and dictation.
    NSTextInsertionIndicatorDisplayModeHidden,
    NSTextInsertionIndicatorDisplayModeVisible,
} NS_SWIFT_NAME(NSTextInsertionIndicator.DisplayMode) API_AVAILABLE(macos(14.0));

typedef NS_OPTIONS(NSInteger, NSTextInsertionIndicatorAutomaticModeOptions) {
    NSTextInsertionIndicatorAutomaticModeOptionsShowEffectsView   = 1 << 0,
    NSTextInsertionIndicatorAutomaticModeOptionsShowWhileTracking  = 1 << 1,
} NS_SWIFT_NAME(NSTextInsertionIndicator.AutomaticModeOptions) API_AVAILABLE(macos(14.0));

API_AVAILABLE(macos(14.0))
@interface NSTextInsertionIndicator : NSView

/// Sets-returns the indicator's display mode.
@property NSTextInsertionIndicatorDisplayMode displayMode;

/// The color of the indicator.
/// @discussion Defaults to NSColor.textInsertionPointColor.
/// @note If set to @c nil, uses NSColor.textInsertionPointColor.
@property(copy, null_resettable) NSColor *color;

/// Options for the NSTextInsertionIndicatorDisplayModeAutomatic display mode.
/// Defaults to NSTextInsertionIndicatorAutomaticModeOptionsShowEffectsView.
@property NSTextInsertionIndicatorAutomaticModeOptions automaticModeOptions;

/// Sets-returns a block that inserts a view into the view hierarchy.
/// @discussion During dictation the NSTextInsertionIndicator displays a glow effect by inserting a view below the text view. If an application needs to insert the view in a different way, the application can specify a block of code that will be called when the glow effect needs to be displayed.
@property (copy, nullable) void (^effectsViewInserter)(NSView *view);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
API_UNAVAILABLE_END
