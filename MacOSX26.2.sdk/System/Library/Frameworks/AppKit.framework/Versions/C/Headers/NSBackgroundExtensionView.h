/*
 NSBackgroundExtensionView.h
 Application Kit
 Copyright (c) 2025, Apple Inc.
 All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <AppKit/NSView.h>

@class CALayer;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

/// A view that extends content to fill its own bounds.
///
/// A background extension view can be laid out to extend outside the safe area,
/// such as under the titlebar, sidebar, or inspector. By default it lays out
/// its content to stay within the safe area, and uses modifications of the
/// content along the edges to fill the container view.
API_AVAILABLE(macos(26.0))
@interface NSBackgroundExtensionView : NSView

/// The content view to extend to fill the `NSBackgroundExtensionView`.
///
/// The content view will be added as a subview of the extension view and
/// placed within the safe area by default. See `automaticallyPlacesContentView`
/// to customize the layout.
@property (nullable, strong) NSView *contentView;

/// Controls the automatic safe area placement of the `contentView` within the
/// container.
///
/// When `NO`, the frame of the content view must be explicitly set or
/// constraints added. The extension effect will be used to fill the container
/// view around the content.
///
/// Defaults to `YES`.
@property (nonatomic, assign) BOOL automaticallyPlacesContentView;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
