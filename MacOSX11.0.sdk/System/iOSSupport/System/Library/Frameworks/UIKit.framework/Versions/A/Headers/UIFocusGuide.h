#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusGuide.h>)
//
//  UIFocusGuide.h
//  UIKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UILayoutGuide.h>
#import <UIKit/UIKitDefines.h>

@protocol UIFocusEnvironment;

NS_ASSUME_NONNULL_BEGIN

/// UIFocusGuides are UILayoutGuide subclasses that participate in the focus system from within their owning view. A UIFocusGuide may be used to expose non-view areas as focusable.
UIKIT_EXTERN API_AVAILABLE(ios(9.0)) @interface UIFocusGuide : UILayoutGuide

/// If disabled, UIFocusGuides are ignored by the focus engine, but still participate in layout. Modifying this flag allows you to conditionally enable or disable certain focus behaviors. YES by default.
@property (nonatomic, getter=isEnabled) BOOL enabled;

/// Setting preferredFocusEnvironments to a non-empty array marks this guide's layoutFrame as focusable. If empty, this guide is effectively disabled.
/// If focused, the guide attempts to redirect focus to each environment in the array, in order, stopping when a focusable item in an environment has been found.
@property (nonatomic, copy, null_resettable) NSArray<id<UIFocusEnvironment>> *preferredFocusEnvironments API_AVAILABLE(ios(10.0));

/// Setting a preferred focused view marks this guide's layoutFrame as focusable, and if focused, redirects focus to its preferred focused view. If nil, this guide is effectively disabled.
@property (nonatomic, weak, nullable) UIView *preferredFocusedView API_DEPRECATED_WITH_REPLACEMENT("preferredFocusEnvironments", ios(9.0, 10.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIFocusGuide.h>
#endif
