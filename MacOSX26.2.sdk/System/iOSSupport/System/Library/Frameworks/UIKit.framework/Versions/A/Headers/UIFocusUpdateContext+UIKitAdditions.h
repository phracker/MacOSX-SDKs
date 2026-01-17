#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusUpdateContext+UIKitAdditions.h>)
//
//  UIFocusUpdateContext+UIKitAdditions.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIFocus.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@interface UIFocusUpdateContext (UIKitAdditions)

/// The view that was focused before the update. May be nil if no view was focused, such as when setting initial focus.
/// If previouslyFocusedItem is not a view, this returns that item's containing view, otherwise they are equal.
/// NOTE: This property will be deprecated in a future release. Use previouslyFocusedItem instead.
@property (nonatomic, weak, readonly, nullable) UIView *previouslyFocusedView;

/// The view that will be focused after the update. May be nil if no view will be focused.
/// If nextFocusedItem is not a view, this returns that item's containing view, otherwise they are equal.
/// NOTE: This property will be deprecated in a future release. Use nextFocusedItem instead.
@property (nonatomic, weak, readonly, nullable) UIView *nextFocusedView;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIFocusUpdateContext+UIKitAdditions.h>
#endif
