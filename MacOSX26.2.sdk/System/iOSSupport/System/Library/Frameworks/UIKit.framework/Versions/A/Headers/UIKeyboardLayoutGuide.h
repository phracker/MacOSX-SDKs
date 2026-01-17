#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIKeyboardLayoutGuide.h>)
//
//  UIKeyboardLayoutGuide.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/UITrackingLayoutGuide.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIKeyboardLayoutGuide : UITrackingLayoutGuide

/**
 The automatic behavior is to follow the keyboard while it is docked (visible and attached to the bottom of the screen). When offscreen or undocked, the topAnchor is tied to the bottomAnchor of the view's @c safeAreaLayoutGuide .
 To follow all keyboard anchors as above even when undocked (detached from the bottom, split and detached, or floating), set @c followsUndockedKeyboard to @c YES.
 When following the keyboard in an undocked state, the guide will update as follows:
     When docked or offscreen, it is considered away from all edges except for the bottom.
     When full-width but undocked or split, it is considered away from the horizontal edges and can be near the top or the bottom.
     When floating, it can be near any one or two adjacent edges at a time.
 Use the methods on @c UITrackingLayoutGuide to set up constraints that automatically activate and deactivate when using @c followsUndockedKeyboard
*/

/// Defaults to @c NO.
@property (nonatomic, readwrite) BOOL followsUndockedKeyboard;

/// Defaults to @c YES. When the keyboard is offscreen, the layout guide is tied to the bottomAnchor of the view's safeAreaLayoutGuide. Set this to @c NO to instead have the guide use the bottomAnchor of the view.
@property (nonatomic, readwrite) BOOL usesBottomSafeArea API_AVAILABLE(ios(17.0));

/// Defaults to 0.0. When a user scrolls to dismiss the keyboard (see @c UIScrollViewKeyboardDismissMode), the gesture waits to start the dismiss until it intersects with the keyboard. This adds padding above the keyboard to start the dismiss earlier. Negative values will be treated as 0.
@property (nonatomic, readwrite) CGFloat keyboardDismissPadding API_AVAILABLE(ios(17.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIKeyboardLayoutGuide.h>
#endif
