#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBackgroundExtensionView.h>)
//
//  UIBackgroundExtensionView.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A view that extends content to fill its own bounds.
///
/// A background extension view can be laid out to extend outside the safe area,
/// such as under a sidebar or an inspector. By default, the view lays out
/// its content to stay within the safe area, and uses modifications of the
/// content along the edges to fill the container view.
API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0))
API_UNAVAILABLE(watchos)
@interface UIBackgroundExtensionView : UIView

/// The content view to extend to fill the `UIBackgroundExtensionView`.
///
/// The content view will be added as a subview of the extension view and
/// placed within the safe area by default. See `automaticallyPlacesContentView` to
/// customize the layout.
@property (nonatomic, strong, nullable) UIView *contentView;

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

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIBackgroundExtensionView.h>
#endif
