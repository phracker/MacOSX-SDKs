#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISearchTab.h>)
//
//  UISearchTab.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UITab.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN NS_SWIFT_UI_ACTOR
API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos)
@interface UISearchTab : UITab

/// Determines if the search tab should automatically activate the embedded search field when the tab becomes visible.
///
/// When this property is set to `YES`, the search field will be activated when the tab is selected. Moreover, when search is cancelled,
/// the previously selected tab in the tab bar will be restored and selected. The default value is `NO`.
@property (nonatomic, assign) BOOL automaticallyActivatesSearch API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(visionos, tvos);

/// Creates a search tab with a system localized title and image.
- (instancetype)initWithViewControllerProvider:(UIViewController *(^_Nullable)(__kindof UITab *))viewControllerProvider NS_DESIGNATED_INITIALIZER;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISearchTab.h>
#endif
