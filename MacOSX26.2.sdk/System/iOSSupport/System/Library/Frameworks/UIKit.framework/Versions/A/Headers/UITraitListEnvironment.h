#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITraitListEnvironment.h>)
//
//  UITraitListEnvironment.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UITrait.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability);

/// Specifies a list appearance that encompasses both UICollectionView & UITableView lists.
typedef NS_ENUM(NSInteger, UIListEnvironment) {
    /// Indicates the absence of any information about whether or not the trait collection is from a view in a list environment.
    UIListEnvironmentUnspecified,
    /// There is no containing list.
    UIListEnvironmentNone,
    /// Contained within a plain-style list.
    UIListEnvironmentPlain,
    /// Contained within a grouped-style list.
    UIListEnvironmentGrouped,
    /// Contained within a inset-grouped-style list.
    UIListEnvironmentInsetGrouped API_UNAVAILABLE(tvos),
    /// Contained within a sidebar-style list.
    UIListEnvironmentSidebar API_UNAVAILABLE(tvos),
    /// Contained within a sidebar-plain-style list.
    UIListEnvironmentSidebarPlain API_UNAVAILABLE(tvos),
} API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

/// A trait that specifies the UIListEnvironment, if any, that a view is in. It is set on views inside UITableViews and list sections in UICollectionViews.
/// Defaults to UIListEnvironmentUnspecified.
UIKIT_EXTERN API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT
@interface UITraitListEnvironment : NSObject <UINSIntegerTraitDefinition>
@end


NS_HEADER_AUDIT_END(nullability, sendability);

#else
#import <UIKitCore/UITraitListEnvironment.h>
#endif
