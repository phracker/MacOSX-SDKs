#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneEnhancedStateRestoration.h>)
//
//  UISceneEnhancedStateRestoration.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIScene.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0)) @interface UIScene (UISceneEnhancedStateRestoration)

- (void)extendStateRestoration;
- (void)completeStateRestoration;

@end

NS_ASSUME_NONNULL_END


#else
#import <UIKitCore/UISceneEnhancedStateRestoration.h>
#endif
