#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneEnhancedStateRestoration.h>)
//
//  UISceneEnhancedStateRestoration.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIScene.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(15.0)) @interface UIScene (UISceneEnhancedStateRestoration)

- (void)extendStateRestoration API_UNAVAILABLE(watchos);
- (void)completeStateRestoration API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UISceneEnhancedStateRestoration.h>
#endif
