/*
    NSGlassEffectView.h
    Application Kit
    Copyright (c) 2025, Apple Inc.
    All rights reserved.
*/


#import <AppKit/NSView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

typedef NS_ENUM(NSInteger, NSGlassEffectViewStyle) {
    /// Standard glass effect style.
    NSGlassEffectViewStyleRegular,
    /// Clear glass effect style.
    NSGlassEffectViewStyleClear
} API_AVAILABLE(macos(26.0)) NS_SWIFT_NAME(NSGlassEffectView.Style);


/// A view that embeds its content view in a dynamic glass effect.
API_AVAILABLE(macos(26.0))
@interface NSGlassEffectView: NSView
/// The view to embed in glass.
///
/// - Important: `NSGlassEffectView` only guarantees the `contentView` will be placed inside the glass effect; arbitrary subviews aren't guaranteed specific behavior with regard to z-order in relation to the content view or glass effect.
@property (nullable, strong) __kindof NSView *contentView;

/// The amount of curvature for all corners of the glass.
@property CGFloat cornerRadius;

/// The color the glass effect view uses to tint the background and glass effect toward.
@property (nullable, copy) NSColor *tintColor;

/// The style of glass this view uses.
@property NSGlassEffectViewStyle style;
@end

/// A view that efficiently merges descendant glass effect views together when they are within a specified proximity to each other.
///
/// - Tip: Using a glass effect container view can improve performance by reducing the number of passes required to render similar glass effect views.
API_AVAILABLE(macos(26.0))
@interface NSGlassEffectContainerView: NSView
/// The view that contains descendant views to merge together when in proximity to each other.
///
/// The glass effect container view does the following:
/// 1. Elevates the z-order of descendants of `contentView` to position them above the `contentView`.
/// 2. Merges descendants together if the views are sufficiently similar and within the proximity specified in ``spacing``.
/// 3. Processes similar glass effect views as a batch to improve performance.
@property (nullable, strong) __kindof NSView *contentView;

/// The proximity at which the glass effect container view begins merging eligible descendent glass effect views.
///
/// The default value, zero, is sufficient for batch processing eligible glass effect views, while avoiding distortion and merging effects for other views in close proximity.
@property CGFloat spacing;
@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
