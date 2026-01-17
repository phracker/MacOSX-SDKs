#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISplitViewControllerLayoutEnvironment.h>)
//
//  UISplitViewControllerLayoutEnvironment.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UITrait.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UISplitViewControllerLayoutEnvironment) {
    /// There is no containing split view controller.
    UISplitViewControllerLayoutEnvironmentNone,
    /// Contained within an expanded split view controller.
    UISplitViewControllerLayoutEnvironmentExpanded,
    /// Contained within a collapsed split view controller.
    UISplitViewControllerLayoutEnvironmentCollapsed
} API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UISplitViewController.LayoutEnvironment);

/// A trait that specifies whether an ancestor split view controller, if any, is expanded or collapsed.
UIKIT_EXTERN API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT
@interface UITraitSplitViewControllerLayoutEnvironment : NSObject <UINSIntegerTraitDefinition>
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISplitViewControllerLayoutEnvironment.h>
#endif
